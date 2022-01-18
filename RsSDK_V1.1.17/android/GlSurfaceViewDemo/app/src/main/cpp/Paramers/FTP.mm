#include "StdAfx.h"
#include "FTP.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	FTP* pThis = (FTP*)userParam;
	RSNet_FtpSet_t* ftp = (RSNet_FtpSet_t*)data;
	pThis->m_Ftp = *ftp;
}

static void RSNET_CALL SoleParamDataCallback(void* data, void* userParam)
{
	FTP* pThis = (FTP*)userParam;
	RSNet_SoleFtpSet_t* soleftp = (RSNet_SoleFtpSet_t*)data;
	pThis->m_SoleFtp = *soleftp;
}

std::string  FTP::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param,'\0',  sizeof(param));

	memset(&m_Ftp,'\0', sizeof(RSNet_FtpSet_t));

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamFtp;
	param.Req = &req;

	param.ParamSize = sizeof(RSNet_FtpSet_t);;
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleFtpSet_t);
	param.ListParamCallback = SoleParamDataCallback;

	param.UserParam = this;

	if(isDefault)
	{
		if (!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}
	else
	{
		if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}	

	//处理数据
	m_obj.clear();
	m_obj["UseFtp"] = m_Ftp.UseFtp;
	m_obj["FtpLoginName"] = (char*)m_Ftp.FtpLoginName;
	m_obj["FtpLoginPwd"] = (char*)m_Ftp.FtpLoginPwd;
	m_obj["useFtpIpAddr2"] = m_Ftp.useFtpIpAddr2;
	m_obj["FtpIpAddr"] = (char*)m_Ftp.FtpIpAddr;
	m_obj["FtpIpAddr2"] = (char*)m_Ftp.FtpIpAddr2;
	m_obj["FtpPort"] = m_Ftp.FtpPort;
	m_obj["SendFileSize"] = m_Ftp.SendFileSize;
	m_obj["FilePath"] = (char*)m_Ftp.FilePath;
	m_obj["ReqTypeMask"] = m_SoleFtp.ReqTypeMask;
	m_obj["VideoSwitch"] = m_Ftp.VideoSwitch;
	m_obj["FtpServer2"] = (char*)m_Ftp.FtpServer2;
	m_obj["EncMode"] = m_Ftp.EncMode;
	m_obj["CertPem"] = (char*)m_Ftp.CertPem;
	m_obj["CertPwd"] = (char*)m_Ftp.CertPwd;
	m_obj["PrivateKey"] = (char*)m_Ftp.PrivateKey;
	m_obj["PrivateKeyPwd"] = (char*)m_Ftp.PrivateKeyPwd;
	m_obj["PicResolution"] = m_Ftp.PicResolution;
	m_obj["PicQulity"] = m_Ftp.PicQulity;
	m_obj["VideoStreamType"] = m_Ftp.VideoStreamType;
	m_obj["EnNormalVideo"] = m_Ftp.EnNormalVideo;
	m_obj["MaxPackInterval"] = m_Ftp.MaxPackInterval;
	m_obj["VideoFormat"] = m_Ftp.VideoFormat;
	for(int i = 0;i < sizeof(m_Ftp.NormalVideoSwitch);++i)
	{
		Json::Value temp = m_Ftp.NormalVideoSwitch[i];
		m_obj["NormalVideoSwitch"].append(temp);
	}
	
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int FTP::SaveAll(std::string strData)
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
		m_Ftp.UseFtp = obj["UseFtp"].asInt();
		m_Ftp.FtpPort = obj["FtpPort"].asInt();
		m_Ftp.SendFileSize = obj["SendFileSize"].asInt();

		int maxLen = sizeof(m_Ftp.FtpLoginName);
		memset(m_Ftp.FtpLoginName, '\0', maxLen);
		m_str = obj["FtpLoginName"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FtpLoginName, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.FtpLoginPwd);
		memset(m_Ftp.FtpLoginPwd, '\0', maxLen);
		m_str = obj["FtpLoginPwd"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FtpLoginPwd, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.FtpIpAddr);
		memset(m_Ftp.FtpIpAddr, '\0', maxLen);
		m_str = obj["FtpIpAddr"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FtpIpAddr, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.FtpIpAddr2);
		memset(m_Ftp.FtpIpAddr2, '\0', maxLen);
		m_str = obj["FtpIpAddr2"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FtpIpAddr2, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.FilePath);
		memset(m_Ftp.FilePath, '\0', maxLen);
		m_str = obj["FilePath"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FilePath, m_str.c_str(), len);

		m_SoleFtp.ReqTypeMask = obj["ReqTypeMask"].asInt();

		m_Ftp.VideoSwitch = obj["VideoSwitch"].asInt();

		maxLen = sizeof(m_Ftp.FtpServer2);
		memset(m_Ftp.FtpServer2, '\0', maxLen);
		m_str = obj["FtpServer2"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.FtpServer2, m_str.c_str(), len);

		m_Ftp.EncMode = obj["EncMode"].asInt();

		maxLen = sizeof(m_Ftp.CertPem);
		memset(m_Ftp.CertPem, '\0', maxLen);
		m_str = obj["CertPem"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.CertPem, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.CertPwd);
		memset(m_Ftp.CertPwd, '\0', maxLen);
		m_str = obj["CertPwd"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.CertPwd, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.PrivateKey);
		memset(m_Ftp.PrivateKey, '\0', maxLen);
		m_str = obj["PrivateKey"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.PrivateKey, m_str.c_str(), len);

		maxLen = sizeof(m_Ftp.PrivateKeyPwd);
		memset(m_Ftp.PrivateKeyPwd, '\0', maxLen);
		m_str = obj["PrivateKeyPwd"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Ftp.PrivateKeyPwd, m_str.c_str(), len);

		m_Ftp.PicResolution = obj["PicResolution"].asInt();
		m_Ftp.PicQulity = obj["PicQulity"].asInt();
		m_Ftp.VideoStreamType = obj["VideoStreamType"].asInt();
		m_Ftp.EnNormalVideo = obj["EnNormalVideo"].asInt();
		m_Ftp.MaxPackInterval = obj["MaxPackInterval"].asInt();
		m_Ftp.VideoFormat = obj["VideoFormat"].asInt();
		for(int i = 0;i < 32;++i)
		{
			m_Ftp.NormalVideoSwitch[i] = obj["NormalVideoSwitch"][i].asInt();
		}
	
	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamFtp;
		param.Param = &m_Ftp;
		param.ListParams = &m_SoleFtp;
		param.ListParamNum = 1;
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