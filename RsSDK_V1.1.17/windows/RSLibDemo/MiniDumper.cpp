#include "stdafx.h"
#include "MiniDumper.h"
#include <assert.h>
#include "dbghelp.h"
#include <time.h>
#pragma comment(lib, "Advapi32.lib")
//#include "FilePath.h"

#ifdef UNICODE
    #define _tcssprintf swprintf_s
	#define tcsplitpath _wsplitpath

    #ifndef _UNICODE
        #define _UNICODE
    #endif
#else
    #define _tcssprintf sprintf_s
	#define tcsplitpath _splitpath
#endif
#include <TCHAR.H>

const int USER_DATA_BUFFER_SIZE = 4096;

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
CMiniDumper* CMiniDumper::s_pMiniDumper = NULL;
LPCRITICAL_SECTION CMiniDumper::s_pCriticalSection = NULL;

// Based on dbghelp.h
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess,
                                         DWORD dwPid,
                                         HANDLE hFile,
                                         MINIDUMP_TYPE DumpType,
                                         CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                         CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                         CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

//-----------------------------------------------------------------------------
// Name: CMiniDumper()
// Desc: Constructor
//-----------------------------------------------------------------------------
CMiniDumper::CMiniDumper( bool bPromptUserForMiniDump,LPCTSTR lpszAppFolder)
{
    memset(&m_szComPath, 0, sizeof(m_szComPath));
    // Our CMiniDumper should act alone as a singleton.
	assert( !s_pMiniDumper );

    s_pMiniDumper = this;
    m_bPromptUserForMiniDump = bPromptUserForMiniDump;

    // The SetUnhandledExceptionFilter function enables an application to 
    // supersede the top-level exception handler of each thread and process.
    // After calling this function, if an exception occurs in a process 
    // that is not being debugged, and the exception makes it to the 
    // unhandled exception filter, that filter will call the exception 
    // filter function specified by the lpTopLevelExceptionFilter parameter.
	::SetUnhandledExceptionFilter( unhandledExceptionHandler );

    // Since DBGHELP.dll is not inherently thread-safe, making calls into it 
    // from more than one thread simultaneously may yield undefined behavior. 
    // This means that if your application has multiple threads, or is 
    // called by multiple threads in a non-synchronized manner, you need to  
    // make sure that all calls into DBGHELP.dll are isolated via a global
    // critical section.
    s_pCriticalSection = new CRITICAL_SECTION;

    if( s_pCriticalSection )
        InitializeCriticalSection( s_pCriticalSection );
	if (lpszAppFolder != NULL)
	{
        /*_tcssprintf(m_szComPath,_T("%s%s"),GetCommonPath(),lpszAppFolder);
        CreateFolder(m_szComPath);*///AS Test
	}
}

//-----------------------------------------------------------------------------
// Name: ~CMiniDumper()
// Desc: Destructor
//-----------------------------------------------------------------------------
CMiniDumper::~CMiniDumper( void )
{
    if( s_pCriticalSection )
    {
        DeleteCriticalSection( s_pCriticalSection );
        delete s_pCriticalSection;
    }
}

//-----------------------------------------------------------------------------
// Name: unhandledExceptionHandler()
// Desc: Call-back filter function for unhandled exceptions
//-----------------------------------------------------------------------------
LONG CMiniDumper::unhandledExceptionHandler( _EXCEPTION_POINTERS *pExceptionInfo )
{
	if( !s_pMiniDumper )
		return EXCEPTION_CONTINUE_SEARCH;

	return s_pMiniDumper->writeMiniDump( pExceptionInfo );
}

//-----------------------------------------------------------------------------
// Name: setMiniDumpFileName()
// Desc: 
//-----------------------------------------------------------------------------
void CMiniDumper::setMiniDumpFileName( void )
{
    time_t currentTime;
    time( &currentTime );
    struct tm tblock;
    localtime_s(&tblock, &currentTime);

    _tcssprintf( m_szMiniDumpPath,MAX_PATH,
                 _T( "%s%s_%4d_%02d_%02d_%02d_%02d_%02d.dmp" ),\
                 _tcslen(m_szComPath)>0?m_szComPath:m_szAppPath,\
                 m_szAppBaseName, tblock.tm_year+1900,tblock.tm_mon+1,\
                 tblock.tm_mday,tblock.tm_hour,tblock.tm_min,tblock.tm_sec);
}

//-----------------------------------------------------------------------------
// Name: getImpersonationToken()
// Desc: The method acts as a potential workaround for the fact that the 
//       current thread may not have a token assigned to it, and if not, the 
//       process token is received.
//-----------------------------------------------------------------------------
bool CMiniDumper::getImpersonationToken( HANDLE* phToken )
{
    *phToken = NULL;

    if( !OpenThreadToken( GetCurrentThread(),
                          TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                          TRUE,
                          phToken) )
    {
        if( GetLastError() == ERROR_NO_TOKEN )
        {
            // No impersonation token for the current thread is available. 
            // Let's go for the process token instead.
            if( !OpenProcessToken( GetCurrentProcess(),
                                   TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                                   phToken) )
                return false;
        }
        else
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
// Name: enablePrivilege()
// Desc: Since a MiniDump contains a lot of meta-data about the OS and 
//       application state at the time of the dump, it is a rather privileged 
//       operation. This means we need to set the SeDebugPrivilege to be able 
//       to call MiniDumpWriteDump.
//-----------------------------------------------------------------------------
BOOL CMiniDumper::enablePrivilege( LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld )
{
    BOOL bOk = FALSE;

    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    bOk = LookupPrivilegeValue( 0, pszPriv, &tp.Privileges[0].Luid );

    if( bOk )
    {
        DWORD cbOld = sizeof(*ptpOld);
        bOk = AdjustTokenPrivileges( hToken, FALSE, &tp, cbOld, ptpOld, &cbOld );
    }

    return (bOk && (ERROR_NOT_ALL_ASSIGNED != GetLastError()));
}

//-----------------------------------------------------------------------------
// Name: restorePrivilege()
// Desc: 
//-----------------------------------------------------------------------------
BOOL CMiniDumper::restorePrivilege( HANDLE hToken, TOKEN_PRIVILEGES* ptpOld )
{
    BOOL bOk = AdjustTokenPrivileges(hToken, FALSE, ptpOld, 0, NULL, NULL);
    return ( bOk && (ERROR_NOT_ALL_ASSIGNED != GetLastError()) );
}

//-----------------------------------------------------------------------------
// Name: writeMiniDump()
// Desc: 
//-----------------------------------------------------------------------------
LONG CMiniDumper::writeMiniDump( _EXCEPTION_POINTERS *pExceptionInfo )
{
	LONG retval = EXCEPTION_CONTINUE_SEARCH;
	m_pExceptionInfo = pExceptionInfo;

    HANDLE hImpersonationToken = NULL;
    if( !getImpersonationToken( &hImpersonationToken ) )
        return FALSE;

	// You have to find the right dbghelp.dll. 
	// Look next to the EXE first since the one in System32 might be old (Win2k)
	
	HMODULE hDll = NULL;
	TCHAR szDbgHelpPath[MAX_PATH];

	if( GetModuleFileName( NULL, m_szAppPath, _MAX_PATH ) )
	{
		TCHAR *pSlash = _tcsrchr( m_szAppPath, _T('\\') );

		if( pSlash )
		{
			_tcscpy_s( m_szAppBaseName, pSlash + 1);
			TCHAR *pDot = _tcsrchr( m_szAppBaseName,_T( '.') );
			if (pDot)
			{
				*pDot = 0;
			}
			*(pSlash+1) = 0;
		}

		_tcscpy_s( szDbgHelpPath, m_szAppPath );
        _tcscat_s( szDbgHelpPath, _T("DBGHELP.DLL") );
		hDll = ::LoadLibrary( szDbgHelpPath );
	}

	if( hDll == NULL )
	{
		// If we haven't found it yet - try one more time.
		hDll = ::LoadLibrary( _T("DBGHELP.DLL") );
	}

	LPCTSTR szResult = NULL;

	if( hDll )
	{
        // Get the address of the MiniDumpWriteDump function, which writes 
        // user-mode mini-dump information to a specified file.
		MINIDUMPWRITEDUMP MiniDumpWriteDump = 
            (MINIDUMPWRITEDUMP)::GetProcAddress( hDll, "MiniDumpWriteDump");

		if( MiniDumpWriteDump != NULL )
        {
			TCHAR szScratch[USER_DATA_BUFFER_SIZE];

			setMiniDumpFileName();

			// Ask the user if he or she wants to save a mini-dump file...
            _tcssprintf( szScratch,MAX_PATH,
                         _T("There was an unexpected error:\n\nWould you ")
                         _T("like to create a mini-dump file?\n\n%s " ),
                         m_szMiniDumpPath);

			// Create the mini-dump file...
			HANDLE hFile = ::CreateFile( m_szMiniDumpPath, 
                                            GENERIC_WRITE, 
                                            FILE_SHARE_WRITE, 
                                            NULL, 
                                            CREATE_ALWAYS, 
                                            FILE_ATTRIBUTE_NORMAL, 
                                            NULL );

			if( hFile != INVALID_HANDLE_VALUE )
			{
				_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
				ExInfo.ThreadId          = ::GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers    = NULL;

                // We need the SeDebugPrivilege to be able to run MiniDumpWriteDump
                TOKEN_PRIVILEGES tp;
                BOOL bPrivilegeEnabled = enablePrivilege( SE_DEBUG_NAME, hImpersonationToken, &tp );

                BOOL bOk;

                // DBGHELP.dll is not thread-safe, so we need to restrict access...
                EnterCriticalSection( s_pCriticalSection );
                {
					// Write out the mini-dump data to the file...
                    bOk = MiniDumpWriteDump( GetCurrentProcess(),
                                                GetCurrentProcessId(),
                                                hFile,
                                                MiniDumpNormal,
                                                &ExInfo,
                                                NULL,
                                                NULL );
                }
                LeaveCriticalSection( s_pCriticalSection );

                // Restore the privileges when done
                if( bPrivilegeEnabled )
	                restorePrivilege( hImpersonationToken, &tp );

                if( bOk )
				{
					szResult = NULL;
					retval = EXCEPTION_EXECUTE_HANDLER;
				}
				else
				{
                    _tcssprintf( szScratch,MAX_PATH,
                                    _T("Failed to save the mini-dump file to '%s' (error %d)"),
                                    m_szMiniDumpPath,
                                    GetLastError() );

					szResult = szScratch;
				}

				::CloseHandle( hFile );
			}
			else
			{
                _tcssprintf( szScratch,MAX_PATH,
                                _T("Failed to create the mini-dump file '%s' (error %d)"),
                                m_szMiniDumpPath,
                                GetLastError() );

				szResult = szScratch;
			}
		}
		else
		{
			szResult = _T( "Call to GetProcAddress failed to find MiniDumpWriteDump. ")
                       _T("The DBGHELP.DLL is possibly outdated." );
		}
	}
	else
	{
		szResult = _T( "Call to LoadLibrary failed to find DBGHELP.DLL." );
	}

	if( szResult && m_bPromptUserForMiniDump )
	{
        TCHAR* pStr = new TCHAR[MAX_PATH];
        _tcssprintf(pStr, MAX_PATH, _T("-----------MiniDumper-----------\n%s\n"), szResult);
        OutputDebugString(pStr);
        delete[] pStr;
	}

	TerminateProcess( GetCurrentProcess(), 0 );

	return retval;
}
