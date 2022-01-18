#include "StdAfx.h"
#include "SendCertificate.h"

SendCertificate::SendCertificate(void)
{
	memset(&m_SoleParam,0,sizeof(RSNet_CertificatesParam_t));
}

SendCertificate::~SendCertificate(void)
{
}

int SendCertificate::SaveAll(std::string strData)
{
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return FALSE;
	}
	int CerType = obj["CerType"].asInt();
	BOOL bInstall = obj["bInstall"].asBool();

#ifdef	WIN32
	std::string pathData = obj["filePath"].asString();
	pathData = UTF8ToAnsi(pathData);
#else//safari
	std::string pathData = obj["filePath"].asString();
#endif
	if (bInstall)
	{
		const char* lpszFileName = pathData.c_str();

		FILE *fp = NULL;  
		if((fp=fopen(lpszFileName,"rb"))==NULL) {  
			printf("File cannot be opened/n");  
			exit(0);  
		}  
		else 
		{
			m_SoleParam.Certype = CerType;

			fseek(fp,0,SEEK_END);
			m_SoleParam.CerLen = (UINT)ftell(fp);
			int size = sizeof(m_SoleParam.Cerbuf);
			if (m_SoleParam.CerLen > size)
			{
				return FALSE;
			}
			int maxLength = m_SoleParam.CerLen;
			int leaveLength = maxLength;
			BYTE* data = &m_SoleParam.Cerbuf[0];
			ZeroMemory(data,m_SoleParam.CerLen);

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
	}
	else
	{
		m_SoleParam.Certype = CerType;
		m_SoleParam.CerLen = 0;
		memset(m_SoleParam.Cerbuf, '\0', sizeof(m_SoleParam.Cerbuf));
	}
	m_SoleParam.Structsize = sizeof(RSNet_CertificatesParam_t);

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamCertificates;
	param.Param = &m_SoleParam;
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}


