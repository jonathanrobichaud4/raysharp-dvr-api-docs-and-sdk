#include "StdAfx.h"
#include "SXHTTPS.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	SXHTTPS * pThis = (SXHTTPS*)userParam;
	memcpy(&pThis->m_Struct, data, sizeof(RSNet_HttpsFileParam_t));
}

std::string  SXHTTPS::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	memset(&m_Struct,0,sizeof(RSNet_HttpsFileParam_t));
	m_Struct.StructSize = sizeof(RSNet_HttpsFileParam_t);

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgHttpsFileParam;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_HttpsFileParam_t);
	param.ParamCallback = ParamDataCallback;

	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["HttpsEnable"] = m_Struct.HttpsEnable;
	m_obj["FileType"] = m_Struct.FileType;
	m_obj["FileExist"] = m_Struct.FileExist;
	m_obj["FileSize"] = (char*)m_Struct.FileSize;
	m_obj["Filebuff"] = (char*)m_Struct.Filebuff;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SXHTTPS::SaveAll(std::string strData)
{	
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	//处理数据
		m_Struct.HttpsEnable = obj["HttpsEnable"].asInt();
		m_Struct.FileType = obj["FileType"].asInt();
		if(obj["FileExist"].isNull()){
			//
		}else{
			m_Struct.FileExist = obj["FileExist"].asInt();
		}
		
		memset((BYTE*)m_Struct.FileSize,'\0',sizeof(m_Struct.FileSize));
		memset((BYTE*)m_Struct.Filebuff,'\0',sizeof(m_Struct.Filebuff));

		if(obj["CerFile"].isNull() || obj["KeyFile"].isNull())
		{
			//no file
		}
		else
		{
			#ifdef	WIN32
				std::string CerFile = obj["CerFile"].asString();
				CerFile = UTF8ToAnsi(CerFile);

				std::string KeyFile = obj["KeyFile"].asString();
				KeyFile = UTF8ToAnsi(KeyFile);
			#else//safari
				std::string CerFile = obj["CerFile"].asString();

				std::string KeyFile = obj["KeyFile"].asString();
			#endif

			const char* lpszCerFile = CerFile.c_str();
			const char* lpszKeyFile = KeyFile.c_str();

			FILE *fpCerFile = fopen(lpszCerFile,"rb");
			FILE *fpKeyFile = fopen(lpszKeyFile,"rb");
			if(fpCerFile==NULL || fpKeyFile==NULL)
			{  
				//printf("File cannot be opened/n");  
				//exit(0); 
				return 10;//FileOpenErr
			}
			else
			{
				fseek(fpCerFile,0,SEEK_END);
				m_Struct.FileSize[0] = (unsigned int)ftell(fpCerFile);

				fseek(fpKeyFile,0,SEEK_END);
				m_Struct.FileSize[1] = (unsigned int)ftell(fpKeyFile);

				unsigned int fileSize = m_Struct.FileSize[0] + m_Struct.FileSize[1];
				unsigned int bufSize = sizeof(m_Struct.Filebuff);
				if(fileSize > bufSize){//存不下
					return 11;//FileSizeErr
				}

				//src
				fseek(fpCerFile,0,SEEK_SET);
				fseek(fpKeyFile,0,SEEK_SET);
				//dst
				BYTE* pRun = &m_Struct.Filebuff[0];
				memset(pRun,'\0',sizeof(m_Struct.Filebuff));

				int nTotalRead = 0;
				while(1)
				{
					int nRead = (unsigned int)fread(pRun,1,1024,fpCerFile);
					if (nRead == 0){
						break;
					}
					pRun += nRead;

					nTotalRead += nRead;
					if(nTotalRead > fileSize){//多读了
						break;
					}
				}
				while(1)
				{
					int nRead = (unsigned int)fread(pRun,1,1024,fpKeyFile);
					if (nRead == 0){
						break;
					}
					pRun += nRead;

					nTotalRead += nRead;
					if(nTotalRead > fileSize){//多读了
						break;
					}
				}

				fclose(fpCerFile);
				fclose(fpKeyFile);
			}
		}

		m_Struct.StructSize = sizeof(RSNet_HttpsFileParam_t);
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgHttpsFileParam;
		param.Param = &m_Struct;

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