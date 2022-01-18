#include "StdAfx.h"
#include "SysParamPTZ.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	SysParamPTZ* pThis = (SysParamPTZ*)userParam;
	RSNet_SolePTZSet_t* channelPTZ = (RSNet_SolePTZSet_t*)data;
	pThis->m_vec.push_back(*channelPTZ);
}

static void RSNET_CALL OneDataCallback(void* data, void* userParam)
{
	SysParamPTZ* pThis = (SysParamPTZ*)userParam;
	memcpy(&pThis->m_Struct,data,sizeof(RSNet_SolePTZSet_t));
}

std::string SysParamPTZ::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamPtz;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SolePTZSet_t);
	param.ListParamCallback = AllDataCallback;
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

void SysParamPTZ::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;

	m_obj["Baudrate"] = m_vec[n].Baudrate;
	m_obj["Check"] = m_vec[n].Check;
	m_obj["DataBit"] = m_vec[n].DataBit;
	m_obj["Number"] = m_vec[n].Number;
	m_obj["Protocol"] = m_vec[n].Protocol;
	m_obj["StopBit"] = m_vec[n].StopBit;
	m_obj["EnablePtzCruise"] = m_vec[n].EnablePtzCruise;
	m_obj["StructSize"] = m_vec[n].StructSize;
	m_obj["SignalType"] = m_vec[n].SignalType;
	m_obj["FocusMode"] = m_vec[n].FocusMode;

}

int SysParamPTZ::SaveAll(std::string strData)
{
	int ret = false;
	int count = 0;
	//int index = 0;
	int Array[256] = {0};
	int nNum = m_pDevice->GetLoginRsp()->AnalogChNum;
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	for(int i=0; i<obj.size(); i++)
	{
		m_vec[i].Baudrate = obj[i]["Baudrate"].asInt();
		m_vec[i].Check = obj[i]["Check"].asInt();
		m_vec[i].DataBit = obj[i]["DataBit"].asInt();
		m_vec[i].Number = obj[i]["Number"].asInt();
		m_vec[i].Protocol = obj[i]["Protocol"].asInt();
		m_vec[i].StopBit = obj[i]["StopBit"].asInt();
		m_vec[i].EnablePtzCruise = obj[i]["EnablePtzCruise"].asInt();
		m_vec[i].SignalType = obj[i]["SignalType"].asInt();
		m_vec[i].FocusMode = obj[i]["FocusMode"].asInt();
	}

	for (int i=0; i<nNum;++i)
	{
		if(m_vec[i].EnablePtzCruise == 1 )//Cruise打开时
		{
			Array[i] = m_vec[i].Number;//存储地址
		}
	}

	for (int i=0; i<nNum-1;++i)
	{
		BOOL bInit = FALSE;
		for (int j=i+1;j<nNum;++j)
		{
			if (Array[i]!= 0 && Array[i] == Array[j])
			{
				bInit = TRUE;
				//index |= 1<<j;
				Array[j] = 0;
				count++;
			}
		}

		if(bInit) { 
			//index |= 1<<i;
			Array[i] = 0;count++;
		}
	}
	UINT uitype = m_pDevice->GetLoginRsp()->UiType;
	if(!(uitype == 50) && !(uitype == 52)){
		if (count > 1)
		{
			//return 5|(index<<32);
			return 5;
		}
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamPtz;
	param.Param = NULL;
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

std::string SysParamPTZ::QueryOne( int n )
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Struct, '\0', sizeof(RSNet_SolePTZSet_t));
	m_Struct.StructSize = sizeof(RSNet_SolePTZSet_t);
	ChannelParamReq req;
	TransformChannelParamReq_One(&req,n);

	param.ParamType = MsgParamPtz;
	param.Req = &req;

	param.ParamSize = 0;
	param.ParamCallback = NULL;

	param.ListParamSize = sizeof(RSNet_SolePTZSet_t);
	param.ListParamCallback = OneDataCallback;
	param.UserParam = this;

	if(!RSNetQueryParam(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	Json::Value temp(Json::arrayValue);
	for(int i = 0;i < RS_MAX_CRUISE_POINT;++i)
	{
		temp.append(m_Struct.ChnCruiseTime[i]);
	}
	m_obj["ChnCruiseTime"] = temp;
	Json::Value Tour(Json::arrayValue);
	for(int i = 0;i < 8;++i)
	{
		Json::Value points(Json::objectValue);
		temp.clear();
		for(int j = 0;j < 32;++j)
		{
			points.clear();
			points["preset"] = m_Struct.Tour[i].points[j].preset;
			points["speed"] = m_Struct.Tour[i].points[j].speed;
			points["delay"] = m_Struct.Tour[i].points[j].delay;
			points["reservel"] = m_Struct.Tour[i].points[j].reservel;
			temp.append(points);
		}
		Tour.append(temp);
	}
	m_obj["Tour"] = Tour;
	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SysParamPTZ::SaveOne( int n,std::string strData )
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
	m_Struct.StructSize = sizeof(RSNet_SolePTZSet_t);
	for(int i = 0;i < 8;++i){
		for(int j = 0;j < 32;++j){
			m_Struct.Tour[i].points[j].preset = obj["Tour"][i][j]["preset"].asUInt();
			m_Struct.Tour[i].points[j].delay = obj["Tour"][i][j]["delay"].asUInt();
			m_Struct.Tour[i].points[j].speed = obj["Tour"][i][j]["speed"].asUInt();
			m_Struct.Tour[i].points[j].reservel = obj["Tour"][i][j]["reservel"].asUInt();
		}
	}

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	if(n <32)
	{
		m_Struct.ChannelMask =  (0x1<<n);
	}
	else
	{
		m_Struct.ChannelMask =  0xFFFF0000 + n;
	}
	param.ParamType = MsgParamPtz;
	param.Param = NULL;
	param.ListParams = &m_Struct;
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
