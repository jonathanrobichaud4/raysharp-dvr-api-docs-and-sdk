#include "StdAfx.h"
#include "AlarmAbnormity.h"

std::string AlarmAbnormity::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));
	memset(listParam, '\0', sizeof(listParam));
	param.ListParamSize = sizeof(RSNet_SoleAbnormalSet_t);
	param.ListParamNum = AlarmMaxNum;
	param.ListParam = listParam;
	param.ParamType = MsgParamAbnormal;

	if(isDefault)
	{
		if(!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param, MsgDefaultParam))
			return strRet;
	}
	else
	{
		if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	Json::Value root(Json::arrayValue);
	for(int i=0; i<AlarmMaxNum; i++)
	{
		StructToJson(i);
		root.append(m_obj);
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void AlarmAbnormity::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	if(n == 0)
	{
		n = 2;
	}
	else if(n == 2)
	{
		n = 0;
	}

	AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
	if(AlarmOutNum > 1)
	{
		Json::Value obj(Json::objectValue);
		for (int i=0; i<AlarmOutNum; ++i)
		{
			obj["item"] = listParam[n].AlarmOutManager[i];
			m_obj["AlarmOutManager"].append(obj);
		}
	}
	for (int i=0; i<3; ++i)
	{
		Json::Value temp(Json::arrayValue);
		for(int j = 0;j < 32;++j)
		{
			temp.append(listParam[n].AlarmOutManagerEx[i][j]);
		}
		m_obj["AlarmOutManagerEx"].append(temp);
		
	}
	m_obj["AlarmOut"] = listParam[n].AlarmOut;
	m_obj["AlarmOutTime"] = listParam[n].AlarmOutTime;
	m_obj["BuzzerMooTime"] = listParam[n].BuzzerMooTime;
	m_obj["Enable"] = listParam[n].Enable;
	m_obj["SendEmail"] = listParam[n].SendEmail;
	m_obj["ShowMessage"] = listParam[n].ShowMessage;
	m_obj["StructSize"] = listParam[n].StructSize;
}

int AlarmAbnormity::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	int ch;
	for(int i=0; i<obj.size(); i++)//0 1 2
	{
		ch = i;//0 1 2
		if(ch == 0){
			ch = 2;
		}else if(ch == 2){
			ch = 0;
		}

		//i=0 ch=2
		//i=1 ch=1
		//i=2 ch=0
		listParam[ch].AlarmOut = obj[i]["AlarmOut"].asInt();
		listParam[ch].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		listParam[ch].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		listParam[ch].Enable = obj[i]["Enable"].asInt();
		listParam[ch].SendEmail = obj[i]["SendEmail"].asInt();
		listParam[ch].ShowMessage = obj[i]["ShowMessage"].asInt();
		listParam[ch].StructSize = sizeof(RSNet_SoleAbnormalSet_t);

		AlarmOutNum = m_pDevice->GetLoginRsp()->AlarmOutNum;
		if (AlarmOutNum > 1)
		{
			for(int j=0; j<AlarmOutNum; j++)
			{
				listParam[ch].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j]["item"].asUInt();
			}
		}
		for(int k = 0;k < 3;++k)
		{
			for(int h = 0;h < 32;++h)
			{
				listParam[ch].AlarmOutManagerEx[k][h] = obj[i]["AlarmOutManagerEx"][k][h].asUInt();
			}
		}
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamAbnormal;
	param.ListParams = listParam;
	param.ListParamNum = AlarmMaxNum;
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
