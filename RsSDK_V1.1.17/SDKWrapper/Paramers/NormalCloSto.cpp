#include "StdAfx.h"
#include "NormalCloSto.h"

std::string NormalCloSto::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_NormalCloudStorageInfo_t));
	m_Struct.StructSize = sizeof(RSNet_NormalCloudStorageInfo_t);
	param.Param = &m_Struct;

	param.ParamSize = sizeof(RSNet_NormalCloudStorageInfo_t);
	param.ParamType = MsgParamCloudStorageInfo;

	if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["Enable"] = m_Struct.Enable;
	m_obj["CloudType"] = m_Struct.CloudType;
	m_obj["key_0"] = (char*)m_Struct.key[0];
	m_obj["key_1"] = (char*)m_Struct.key[1];
	m_obj["secret_0"] = (char*)m_Struct.secret[0];
	m_obj["secret_1"] = (char*)m_Struct.secret[1];
	m_obj["FTPPATH"] = (char*)m_Struct.FTPPATH;
	m_obj["Channel"] = m_Struct.Channel;
	m_obj["TimeTrigger"] = m_Struct.TimeTrigger;
	m_obj["MotionEnable"] = m_Struct.MotionEnable;
	m_obj["DriveName"] = (char*)m_Struct.DriveName;
	for(int i = 0; i < 8; ++ i)
	{
		m_obj["Channel_EX"].append(m_Struct.Channel_EX[i]);
	}

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int NormalCloSto::SaveAll(std::string strData)
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
		m_Struct.Enable = obj["Enable"].asInt();
		m_Struct.CloudType = obj["CloudType"].asInt();
		m_Struct.Channel = (unsigned int)obj["Channel"].asDouble();
		m_Struct.TimeTrigger = obj["TimeTrigger"].asInt();
		m_Struct.MotionEnable = obj["MotionEnable"].asInt();

		//用key[0]
		int maxLen = sizeof(m_Struct.key[0]);
		memset(m_Struct.key[0], '\0', maxLen);
		m_str = obj["key_0"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.key[0], m_str.c_str(), len);

		//用key[1]
		maxLen = sizeof(m_Struct.key[1]);
		memset(m_Struct.key[1], '\0', maxLen);
		m_str = obj["key_1"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.key[1], m_str.c_str(), len);

		//secret[0]
		maxLen = sizeof(m_Struct.secret[0]);
		memset(m_Struct.secret[0], '\0', maxLen);
		m_str = obj["secret_0"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.secret[0], m_str.c_str(), len);

		//secret[1]
		maxLen = sizeof(m_Struct.secret[1]);
		memset(m_Struct.secret[1], '\0', maxLen);
		m_str = obj["secret_1"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.secret[1], m_str.c_str(), len);	

		maxLen = sizeof(m_Struct.FTPPATH);
		memset(m_Struct.FTPPATH, '\0', maxLen);
		m_str = obj["FTPPATH"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.FTPPATH, m_str.c_str(), len);

		maxLen = sizeof(m_Struct.DriveName);
		memset(m_Struct.DriveName, '\0', maxLen);
		m_str = obj["DriveName"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Struct.DriveName, m_str.c_str(), len);

		for(int j = 0;j < 8;++j)
		{
			m_Struct.Channel_EX[j] = obj["Channel_EX"][j].asUInt();
		}

	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamCloudStorageInfo;
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