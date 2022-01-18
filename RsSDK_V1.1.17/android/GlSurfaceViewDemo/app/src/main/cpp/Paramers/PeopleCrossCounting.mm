#include "StdAfx.h"
#include "PeopleCrossCounting.h"

static void RSNET_CALL AllDataCallback(void* data, void* userParam)
{
	PeopleCrossCounting* pThis = (PeopleCrossCounting*)userParam;
	RSNet_SoleIntHumanFace_t* PeopleCC = (RSNet_SoleIntHumanFace_t*)data;
	pThis->m_vec.push_back(*PeopleCC);
}

std::string PeopleCrossCounting::QueryAll(bool bDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIntPCC;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleIntHumanFace_t);
	param.ListParamCallback = AllDataCallback;
	param.UserParam = this;

	if(bDefault)
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

void PeopleCrossCounting::StructToJson(int n)
{
	m_obj.clear();
	m_obj["ch"] = n;
	
	m_obj["ChnSwitch"] = m_vec[n].ChnSwitch;
	m_obj["BuzzerMooTime"] = m_vec[n].BuzzerMooTime;
	m_obj["AlarmOutTime"] = m_vec[n].AlarmOutTime;
	m_obj["RecordDelayTime"] = m_vec[n].RecordDelayTime;
	for(int i = 0;i < 4;++i)
	{
		m_obj["AlarmOutManager"].append(m_vec[n].AlarmOutManager[i]);
	}
	m_obj["RecordChannel"] = m_vec[n].RecordChannel;
	m_obj["Record"] = m_vec[n].Record;
	m_obj["ShowMessage"] = m_vec[n].ShowMessage;
	m_obj["SendEmail"] = m_vec[n].SendEmail;
	m_obj["FullScreen"] = m_vec[n].FullScreen;
	m_obj["RuleSwitch"] = m_vec[n].RuleSwitch;
	m_obj["RuleType"] = m_vec[n].RuleType;
	m_obj["RuleTypeAdd"] = m_vec[n].RuleTypeAdd;
	m_obj["RuleScene"] = m_vec[n].RuleScene;
	m_obj["Sensitive"] = m_vec[n].Sensitive;
	m_obj["DrawLineEnable"] = m_vec[n].DrawLineEnable;
	m_obj["sendToFTP"] = m_vec[n].sendToFTP;
	m_obj["IVALines"] = m_vec[n].IVALines;
	m_obj["PushSwitch"] = m_vec[n].PushSwitch;
	
	for(int i = 0;i < 32;++i)
	{
		Json::Value val(Json::objectValue);
		val["x1"] = m_vec[n].RuleLine[i].x1 < 0 ? 0 : m_vec[n].RuleLine[i].x1;
		val["y1"] = m_vec[n].RuleLine[i].x1 < 0 ? 0 : m_vec[n].RuleLine[i].y1;
		val["x2"] = m_vec[n].RuleLine[i].x1 < 0 ? 0 : m_vec[n].RuleLine[i].x2;
		val["y2"] = m_vec[n].RuleLine[i].x1 < 0 ? 0 : m_vec[n].RuleLine[i].y2;
		m_obj["RuleLine"].append(val);
	}

	for(int i=0; i<8; ++i)
	{
		m_obj["RecordChannel_EX"].append(m_vec[n].RecordChannel_EX[i]);
	}
	for (int i=0;i<3;++i)
	{
		Json::Value tempMotionmang(Json::arrayValue);
		for(int j=0;j<32;++j)
		{
			tempMotionmang.append(m_vec[n].AlarmOutManagerEx[i][j]);

		}
		m_obj["AlarmOutManagerEx"].append(tempMotionmang);
	}
	m_obj["FtpLink"] = m_vec[n].FtpLink;
	m_obj["FtpVideoLink"] = m_vec[n].FtpVideoLink;
	m_obj["CloudPicUpload"] = m_vec[n].CloudPicUpload;
	m_obj["CloudVideoUpload"] = m_vec[n].CloudVideoUpload;
}

int PeopleCrossCounting::SaveAll(std::string strData)
{
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
		m_vec[i].ChnSwitch = obj[i]["ChnSwitch"].asInt();
		m_vec[i].BuzzerMooTime = obj[i]["BuzzerMooTime"].asInt();
		m_vec[i].AlarmOutTime = obj[i]["AlarmOutTime"].asInt();
		m_vec[i].RecordDelayTime = obj[i]["RecordDelayTime"].asInt();
		for(int j = 0;j < obj[i]["AlarmOutManager"].size();++j)
		{
			m_vec[i].AlarmOutManager[j] = obj[i]["AlarmOutManager"][j].asInt();
		}

		m_vec[i].RecordChannel = (unsigned int)obj[i]["RecordChannel"].asDouble();
		m_vec[i].Record = obj[i]["Record"].asInt();
		m_vec[i].ShowMessage = obj[i]["ShowMessage"].asInt();
		m_vec[i].SendEmail = obj[i]["SendEmail"].asInt();
		m_vec[i].FullScreen = obj[i]["FullScreen"].asInt();
		m_vec[i].RuleSwitch = obj[i]["RuleSwitch"].asInt();
		m_vec[i].RuleType = obj[i]["RuleType"].asInt();
		m_vec[i].RuleTypeAdd = obj[i]["RuleTypeAdd"].asInt();
		m_vec[i].RuleScene = obj[i]["RuleScene"].asInt();
		m_vec[i].Sensitive = obj[i]["Sensitive"].asInt();
		m_vec[i].DrawLineEnable = obj[i]["DrawLineEnable"].asInt();
		m_vec[i].sendToFTP = obj[i]["sendToFTP"].asInt();
		m_vec[i].IVALines = obj[i]["IVALines"].asInt();
		m_vec[i].PushSwitch = obj[i]["PushSwitch"].asInt();
		m_vec[i].StructSize = sizeof(RSNet_SoleIntHumanFace_t);
		
		for(int j = 0;j < obj[i]["RuleLine"].size();++j)
		{
			m_vec[i].RuleLine[j].x1 = obj[i]["RuleLine"][j]["x1"].asInt();
			m_vec[i].RuleLine[j].y1 = obj[i]["RuleLine"][j]["y1"].asInt();
			m_vec[i].RuleLine[j].x2 = obj[i]["RuleLine"][j]["x2"].asInt();
			m_vec[i].RuleLine[j].y2 = obj[i]["RuleLine"][j]["y2"].asInt();
		}

		for(int j=0; j<obj[i]["RecordChannel_EX"].size(); j++)
		{
			m_vec[i].RecordChannel_EX[j] = (unsigned int)obj[i]["RecordChannel_EX"][j].asDouble();
		}
		for (int j=0;j<3;++j)
		{
			for(int k=0;k<32;++k)
			{
				m_vec[i].AlarmOutManagerEx[j][k] = obj[i]["AlarmOutManagerEx"][j][k].asUInt();
			}
		}
		m_vec[i].FtpLink = obj[i]["FtpLink"].asInt();
		m_vec[i].FtpVideoLink = obj[i]["FtpVideoLink"].asInt();
		m_vec[i].CloudPicUpload = obj[i]["CloudPicUpload"].asInt();
		m_vec[i].CloudVideoUpload = obj[i]["CloudVideoUpload"].asInt();
	}

	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamIntPCC;
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