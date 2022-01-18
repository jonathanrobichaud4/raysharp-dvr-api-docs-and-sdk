#include "StdAfx.h"
#include "AnalogCh.h"


//һ�λ��һ��ͨ��������
static void RSNET_CALL ListParamCallback(void* data, void* userParam)
{
	AnalogCh* pThis = (AnalogCh*)userParam;	
	RSNet_SoleAnalogCam_t* SoleInfo = (RSNet_SoleAnalogCam_t*)data;
	pThis->m_vec.push_back(*SoleInfo);
}

std::string AnalogCh::QueryAll(bool isDefault)
{
	//��������
	std::string strRet = "err";

	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));
	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);
	param.Req = &req;
	param.ParamType = MsgParamAnalogCam;

	param.ListParamSize = sizeof(RSNet_SoleAnalogCam_t);
	param.ListParamCallback = ListParamCallback;//��ѯ�����ݺ�ʹ�ô˺�������
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

	//��������
	Json::Value root(Json::arrayValue);
	for(int i=0; i<m_vec.size(); i++)
	{
		if(i < m_pDevice->GetAnalogChNum())
		{
			//��ҳֻ��Ҫģ��ͨ��������
			StructToJson(i);
			root.append(m_obj);
		}
	}

	Json::FastWriter writer;
	strRet = writer.write(root);
	return strRet;
}

void AnalogCh::StructToJson(int i)
{
	m_obj.clear();
	m_obj["ch"] = i;
	m_obj["NewNameFlag"] = m_vec[i].NewNameFlag;
	m_obj["ChnName"] = (char *)m_vec[i].ChnName;
	m_obj["ExtendChnNameMask"] = (char *)m_vec[i].ExtendChnNameMask;
	m_obj["Status"] = m_vec[i].Status;
}

//����
int AnalogCh::SaveAll(std::string strData)
{
	//��������
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
		if(i < m_pDevice->GetAnalogChNum())
		{
			//ģ��ͨ��
			m_vec[i].Status = obj[i]["Status"].asInt();
		}
	}

	//��������
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamAnalogCam;
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