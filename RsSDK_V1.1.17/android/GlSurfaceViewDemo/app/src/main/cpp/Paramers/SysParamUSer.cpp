#include "StdAfx.h"
#include "SysParamUSer.h"

static void RSNET_CALL ParamDataCallback(void* data, void* userParam)
{
	SysParamUSer* pThis = (SysParamUSer*)userParam;
	RSNet_UserSet_t* UserSet = (RSNet_UserSet_t*)data;
	pThis->m_UserSet = *UserSet;
}

static void RSNET_CALL SoleParamDataCallback(void* data, void* userParam)
{
	SysParamUSer* pThis = (SysParamUSer*)userParam;
	RSNet_SoleUserInfo_t* SoleUserInfo = (RSNet_SoleUserInfo_t*)data;
	pThis->m_vec.push_back(*SoleUserInfo);
}

std::string SysParamUSer::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	
	m_vec.clear();

	param.ParamType = MsgParamUser;

	param.ParamSize = sizeof(RSNet_UserSet_t);
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleUserInfo_t);
	param.ListParamCallback = SoleParamDataCallback;

	param.UserParam = this;
	
	if(bDefault)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

std::string SysParamUSer::QueryAll(std::string strData)
{
	//请求数据
	std::string strRet = "err";
	
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return strRet;
	}

	m_nClient = obj["nClient"].asUInt();

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	param.ParamType = MsgParamUser;

	param.ParamSize = sizeof(RSNet_UserSet_t);
	param.ParamCallback = ParamDataCallback;

	param.ListParamSize = sizeof(RSNet_SoleUserInfo_t);
	param.ListParamCallback = SoleParamDataCallback;

	param.UserParam = this;

	if(0)
	{
		if(!RSNetQueryDefaultParam(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void SysParamUSer::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	if(165 == m_nClient)
	{
		//没用到
		m_obj["Password"] = "********";
		m_obj["Password2"] = "********";
		
		int nLen = strlen((char*)m_vec[n].c32Password);
		if(nLen){
			m_obj["IsHavePsw"] = 1;
			m_obj["c32Password"] = "*************";
		}else{
			m_obj["IsHavePsw"] = 0;
			m_obj["c32Password"] = "";
		}
		m_obj["bChangedPsw"] = 0;//是否修改了密码
	}
	else
	{
		m_obj["Password"] = (char*)m_vec[n].Password;
		m_obj["Password2"] = (char*)m_vec[n].Password2;
		m_obj["c32Password"] = (char*)m_vec[n].c32Password;
	}

	m_obj["UserName"] = (char*)m_vec[n].UserName;
	m_obj["HaveSwitch"] = m_vec[n].HaveSwitch;
	m_obj["HaveUser"] = m_vec[n].HaveUser;
	m_obj["UserStatus"] = m_vec[n].UserStatus;
	m_obj["UserSetRight"] = m_vec[n].UserRights.UserSetRight;
	m_obj["PreviewChannel"] = m_vec[n].UserRights.PreviewChannel;
	m_obj["PlayBackChannel"] = m_vec[n].UserRights.PlayBackChannel;
	m_obj["BackupChannel"] = m_vec[n].UserRights.BackupChannel;
	m_obj["PtzControlChannel"] = m_vec[n].UserRights.PtzControlChannel;
	m_obj["UserPreview"] = m_vec[n].UserRights.UserPreview;
	m_obj["UserPlayBack"] = m_vec[n].UserRights.UserPlayBack;
	m_obj["UserBackup"] = m_vec[n].UserRights.UserBackup;
	m_obj["UserPtzControl"] = m_vec[n].UserRights.UserPtzControl;
	m_obj["UserName2"] = (char*)m_vec[n].c32UserName;
	m_obj["UserRtsp"] = m_vec[n].UserRights.UserRtsp;
	m_obj["OnivfRight"] = m_vec[n].UserRights.OnivfRight;

	Json::Value obj(Json::objectValue);

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].PreviewChannel_EX[i];
		m_obj["PreviewChannel_EX"].append(obj);
	}
		
	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].PlayBackChannel_EX[i];
		m_obj["PlayBackChannel_EX"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].BackupChannel_EX[i];
		m_obj["BackupChannel_EX"].append(obj);
	}

	for(int i=0; i<8; i++)
	{
		obj["item"] = m_vec[n].PtzControlChannel_EX[i];
		m_obj["PtzControlChannel_EX"].append(obj);
	}
}

int SysParamUSer::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	if(0 == m_vec.size()){
		return false;//刷新失败数组为0
	}

	//处理数据
		int i = 0;
		if(!obj[i]["needCheckPswSame"].isNull())
		{
			for(int i=0; i<obj.size(); i++)
			{
				if(0 == obj[i]["bChangedPsw"].asUInt()){//密码没修改
					continue;
				}
				std::string strLeft = obj[i]["c32Password"].asString();

				for(int j=0; j<obj.size(); j++)
				{
					if(j==i){
						continue;
					}
					std::string strRight;
					if(obj[j]["bChangedPsw"].asUInt()){//密码有修改
						strRight = obj[j]["c32Password"].asString();
					}else{
						strRight = (char*)m_vec[j].c32Password;
					}

					if( strcmp(strLeft.c_str(),strRight.c_str()) == 0 )//the same
					{
						return 21;//CheckPswSame
					}
				}
			}
		}

		i = 0;
		if(!obj[i]["CheckCurPsw"].isNull())
		{
			int ret = strcmp(obj[i]["CheckCurPsw"].asString().c_str(), m_pDevice->m_strPassword.c_str());
			if(ret == 0){
				//CheckCurPsw_ok
			}else{
				return 22;//CheckCurPsw_failure
			}
		}
		
		for(int i=0; i<obj.size(); i++)
		{
			int maxLen = sizeof(m_vec[i].UserName);
			memset(m_vec[i].UserName, '\0', maxLen);
			m_str = obj[i]["UserName"].asString();
			int len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].UserName, m_str.c_str(), len);

			
			if(165 == m_nClient)
			{
				//do not save
			}
			else
			{
				maxLen = sizeof(m_vec[i].Password);
				memset(m_vec[i].Password, '\0', maxLen);
				m_str = obj[i]["Password"].asString();
				len = m_str.length() < maxLen ? m_str.length() : maxLen;
				memcpy(m_vec[i].Password, m_str.c_str(), len);

				maxLen = sizeof(m_vec[i].Password2);
				memset(m_vec[i].Password2, '\0', maxLen);
				m_str = obj[i]["Password2"].asString();
				len = m_str.length() < maxLen ? m_str.length() : maxLen;
				memcpy(m_vec[i].Password2, m_str.c_str(), len);
			}

			int bSave32Psw = true;
			if(!obj[i]["bChangedPsw"].isNull())//存在
			{
				bSave32Psw = obj[i]["bChangedPsw"].asUInt();
			}
			if(bSave32Psw){
				maxLen = sizeof(m_vec[i].c32Password);
				memset(m_vec[i].c32Password, '\0', maxLen);
				m_str = obj[i]["c32Password"].asString();
				len = m_str.length() < maxLen ? m_str.length() : maxLen;
				memcpy(m_vec[i].c32Password, m_str.c_str(), len);
			}

			maxLen = sizeof(m_vec[i].c32UserName);
			memset(m_vec[i].c32UserName, '\0', maxLen);
			m_str = obj[i]["UserName2"].asString();
			len = m_str.length() < maxLen ? m_str.length() : maxLen;
			memcpy(m_vec[i].c32UserName, m_str.c_str(), len);

			m_vec[i].HaveSwitch = obj[i]["HaveSwitch"].asUInt();
			m_vec[i].HaveUser = obj[i]["HaveUser"].asUInt();

			if (i == 0)
			{
				continue;
			}

			m_vec[i].UserRights.UserSetRight = obj[i]["UserSetRight"].asUInt();
			m_vec[i].UserRights.PreviewChannel = obj[i]["PreviewChannel"].asUInt();
			m_vec[i].UserRights.PlayBackChannel = obj[i]["PlayBackChannel"].asUInt();
			m_vec[i].UserRights.BackupChannel = obj[i]["BackupChannel"].asUInt();
			m_vec[i].UserRights.PtzControlChannel = obj[i]["PtzControlChannel"].asUInt();
			m_vec[i].UserRights.UserPreview = obj[i]["UserPreview"].asUInt();
			m_vec[i].UserRights.UserPlayBack = obj[i]["UserPlayBack"].asUInt();
			m_vec[i].UserRights.UserBackup = obj[i]["UserBackup"].asUInt();
			m_vec[i].UserRights.UserPtzControl = obj[i]["UserPtzControl"].asUInt();
			m_vec[i].UserRights.UserRtsp = obj[i]["UserRtsp"].asUInt();
			m_vec[i].UserRights.OnivfRight = obj[i]["OnivfRight"].asUInt();

			for(int j = 0;j < 8;++j)
			{
				m_vec[i].PreviewChannel_EX[j] = (unsigned int)obj[i]["PreviewChannel_EX"][j]["item"].asDouble();
				m_vec[i].PlayBackChannel_EX[j] = (unsigned int)obj[i]["PlayBackChannel_EX"][j]["item"].asDouble();
				m_vec[i].BackupChannel_EX[j] = (unsigned int)obj[i]["BackupChannel_EX"][j]["item"].asDouble();
				m_vec[i].PtzControlChannel_EX[j] = (unsigned int)obj[i]["PtzControlChannel_EX"][j]["item"].asDouble();
			}
		}

	//保存数据
		RSNetSetParamParam param;
		memset(&param, '\0', sizeof(param));
		param.ParamType = MsgParamUser;
		param.Param = &m_UserSet;
		param.ListParams = &m_vec[0];
		param.ListParamNum = m_vec.size();
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

int SysParamUSer::ModifyPassword(std::string strData)
{
	if(QueryAll() != "err")
	{
		if(!m_vec.empty())
		{
			//处理数据
			int i=0;
			int maxLen = sizeof(m_vec[i].Password);
			memset(m_vec[i].Password, '\0', maxLen);
			int len = strData.length() < maxLen ? strData.length() : maxLen;
			memcpy(m_vec[i].Password, strData.c_str(), len);

			maxLen = sizeof(m_vec[i].Password2);
			memset(m_vec[i].Password2, '\0', maxLen);
			len = strData.length() < maxLen ? strData.length() : maxLen;
			memcpy(m_vec[i].Password2, strData.c_str(), len);

			maxLen = sizeof(m_vec[i].c32Password);
			memset(m_vec[i].c32Password, '\0', maxLen);
			len = strData.length() < maxLen ? strData.length() : maxLen;
			memcpy(m_vec[i].c32Password, strData.c_str(), len);

			/*maxLen = sizeof(m_vec[i].c32Password2);
			memset(m_vec[i].c32Password2, '\0', maxLen);
			len = strData.length() < maxLen ? strData.length() : maxLen;
			memcpy(m_vec[i].c32Password2, strData.c_str(), len);*/

			//保存数据
			RSNetSetParamParam param;
			memset(&param, '\0', sizeof(param));
			param.ParamType = MsgParamUser;
			param.Param = &m_UserSet;
			param.ListParams = &m_vec[0];
			param.ListParamNum = m_vec.size();
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
	}

	return false;
}