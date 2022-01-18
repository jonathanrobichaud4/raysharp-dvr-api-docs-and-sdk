#include "StdAfx.h"
#include "GetSetParam.h"

CGetSetParam::CGetSetParam(void)
{
	m_SoleParam = new RemoteNewParamBackupResp_t;
}

CGetSetParam::~CGetSetParam(void)
{
	delete m_SoleParam;
}

static void RSNET_CALL ExportBackupCallback(void* data, UINT size, void* userParam)
{
	CGetSetParam* pThis = (CGetSetParam*)userParam;
	if(pThis != NULL && data != NULL && size > 0 ){
		pThis->ExpParam(data,size);
	}
}

int CGetSetParam::ExpParam(void* data,UINT size){
	int TotalNum = sizeof(RemoteNewParamBackupResp_t);
	//int TotalNum = sizeof(m_SoleParam);
	if (size <= TotalNum) {
		memset(m_SoleParam, 0, TotalNum);
		memcpy(m_SoleParam, data, size);
		return TRUE;
	} else {
		return FALSE;
	}
}

int CGetSetParam::SaveAll(std::string strData)
{
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return FALSE;
	}
#ifdef	WIN32
	std::string pathData = obj["filePath"].asString();
	std::string nameData = obj["fileName"].asString();
	pathData = UTF8ToAnsi(pathData);
	nameData = UTF8ToAnsi(nameData);
#else//safari
	std::string pathData = obj["filePath"].asString();
	std::string nameData = obj["fileName"].asString();
#endif
	if (pathData != "" && nameData != "")
	{
		const char* lpszFileName = pathData.c_str();

		FILE *fp = NULL;  
		if((fp=fopen(lpszFileName,"rb"))==NULL) {  
			printf("File cannot be opened/n");  
			exit(0);  
		}  
		else 
		{
			std::string strTemp= nameData;
			int lenStr = sizeof(m_SoleParam->filename);
			ZeroMemory(m_SoleParam->filename, lenStr);
			strcpy(m_SoleParam->filename, strTemp.c_str());

			fseek(fp,0,SEEK_END);
			m_SoleParam->paramLen = (UINT)ftell(fp);
			int size = sizeof(m_SoleParam->respInfo);
			if (m_SoleParam->paramLen > size)
			{
				return FALSE;
			}
			int maxLength = m_SoleParam->paramLen;
			int leaveLength = maxLength;
			char* data = &m_SoleParam->respInfo[0];
			ZeroMemory(data,m_SoleParam->paramLen);

			fseek(fp,0,SEEK_SET);
			while (leaveLength) {
				int length = (UINT)fread(data,1,leaveLength,fp);//cFile.Read(data, leaveLength);//尽可能多的读取文件
				if (length == 0)
					break;
				data += length;
				leaveLength -= length;
			}
		}
		fclose(fp);
		m_SoleParam->structSize = m_SoleParam->paramLen + 40;
	}

	RemoteNewParamBackupResp_t param;
	memset(&param, 0, sizeof(param));

	param =*m_SoleParam;

	//if(RSNetRemoteParamImport(m_pDevice->GetConnection(), &param)){
	if(RSNetRemoteParamImportNew(m_pDevice->GetConnection(), &param)){
		return TRUE;
	}
	return FALSE;
}

std::string CGetSetParam::QueryAll(std::string strData)  //请求
{
	std::string strRst = "err",pathStr="",nameStr="";
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return strRst;
	}

#ifdef	WIN32
	pathStr = obj["filePath"].asString();
#else//safari
	pathStr = obj["filePath"].asString();
#endif

	if (pathStr != "")//export
	{
		RSNetExportBackupParam param;
		ZeroMemory(&param,sizeof(param));
		memset(m_SoleParam,0,sizeof(RemoteNewParamBackupResp_t));

		param.DataCallback = ExportBackupCallback;
		param.UserParam = this;

		if (RSNetExportBackupNew(m_pDevice->GetConnection(), &param)){
//#ifdef	WIN32
#if 0		//lxj
			char temp_path[MAX_PATH] = {0};
			sprintf_s(temp_path, sizeof(temp_path), "%s\\%s", pathStr.c_str(), m_SoleParam->filename);
			std::wstring strtemp = UTF8ToUnicode(temp_path);
			CString fileName(strtemp.c_str());
			int fileSize = m_SoleParam->paramLen;

			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			CString strFilter = _T("RS Param File (*)|");
			CFileDialog dlg(FALSE,NULL,fileName.GetBuffer(),OFN_PATHMUSTEXIST|OFN_CREATEPROMPT, strFilter );
			dlg.m_ofn.lpstrTitle = _T("Please input the param file name");
			if ( IDOK == dlg.DoModal() ){
				fileName = dlg.GetPathName();
				CString pszFileName=fileName;

				CFile cFile;
				if (cFile.Open(pszFileName.GetBuffer(0), CFile::modeCreate|CFile::modeReadWrite | CFile::typeBinary))
				{
					int leaveLength = fileSize;
					char* data = &m_SoleParam->respInfo[0];
					while (leaveLength) {
						if (leaveLength<1024)
						{
							cFile.Write(data, leaveLength);
							break;
						}else{
							cFile.Write(data, 1024);
							data += 1024;
							leaveLength = leaveLength-1024;
						}
					}
					strRst = "suc";
				}
				cFile.Close();
			} 
#else//safari
            std::string filename = m_SoleParam->filename;//lxj
            if(filename.empty()) { filename = "ipcParamPage";}
            
            std::string filepath =pathStr + filename;
            const char* constfilepath = filepath.c_str();
            FILE *pfile = NULL;
            pfile = fopen(constfilepath,"wb");
            
            char* buffer = &m_SoleParam->respInfo[0];
            if(buffer != NULL){
                fwrite(m_SoleParam->respInfo,sizeof(char),m_SoleParam->paramLen,pfile);
                fclose(pfile);
                strRst = "suc";
            }
#endif	
	    }
    }

	return strRst;
}


