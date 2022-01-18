#include "StdAfx.h"
#include "JsonPage.h"

static void RSNET_CALL ParamDataCallback(const char* param, int size, void* user_param)
{
	JsonPage * pThis = (JsonPage*)user_param;
	pThis->m_Net = param;
}

static void RSNET_CALL SetParamJsonCallback(int status, const char* param, int size, void* user_param)
{
	JsonPage* pThis = (JsonPage*)user_param;
	if (pThis != NULL){
		Json::Reader reader;
		Json::Value obj;
		Json::Value data;
		if(!reader.parse(param, obj))
		{
			data["ParamData"] = "JsonPage json parse err.";
			data["Page"] = MsgJsonTypeMsg;
			pThis->m_pDevice->SendMsgToWeb(SubMsgSetParameter,MsgGetAndSetParamEvent,data,NULL);
			pThis->m_SetParamHandle = NULL;
			return;
		}
		else
		{
			Json::Value temp;
			data["ParamData"] = obj;
			data["ParamData"]["result"] = obj["data"]["result"];
			data["Page"] = MsgJsonTypeMsg;
			pThis->m_pDevice->SendMsgToWeb(SubMsgSetParameter,MsgGetAndSetParamEvent,data,NULL);
			pThis->m_SetParamHandle = NULL;
		}
	}
}

static void RSNET_CALL GetParamDataCallback(const char* param, int size, void* user_param)
{
	//�첽ˢ��δʵ��
	int a = 1;
}
std::string JsonPage::QueryAll(std::string strData)
{
	//��������
    m_Net = "err";

	if(strData == ""){
		return m_Net;
	}
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return m_Net;
	}


	QueryParamJsonInfo param;
	memset(&param,'\0',  sizeof(param));
	param.main_msg_type = MsgJsonTypeMsg;
	param.user_param = this;

	param.param = strData.c_str();
	param.param_size = strData.length();

	if(1/*obj["Async"].isNull() || !obj["Async"].asBool()*/)//�첽ˢ��δд���Ȳ�Ҫʹ��
	{
		param.callback = ParamDataCallback;
		if (RSNetQueryParamJson(m_pDevice->GetConnection(), &param))
			return m_Net;

		return m_Net;
	}
	else
	{
		param.callback = GetParamDataCallback;
		if (RSNetAsyncStartQueryParamJson(m_pDevice->GetConnection(),&param))
			return "Async suc";
		return "Async err";
	}
}

int JsonPage::SaveAll(std::string strData)
{
	if(m_SetParamHandle != NULL)//�ϴ�����δ����
	{
		return -3;
	}
	if(strData == "null"){
		return false;
	}
	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}
	
	SetParamJsonInfo param = {0};
	param.main_msg_type = MsgJsonTypeMsg;

	param.param = strData.c_str();
	param.param_size = strData.length();
	param.callback = SetParamJsonCallback;
	param.user_param = this;
	if(obj["Async"].isNull() || !obj["Async"].asBool())
	{
		if (RSNetSetParamJson(m_pDevice->GetConnection(), &param))
			return true;

		return false;
	}
	else
	{
		param.erase_after_callback = TRUE;
		m_SetParamHandle = RSNetAsyncStartSetParamJson(m_pDevice->GetConnection(),&param);//�첽�ɹ�ʧ�ܲ�����ͬ���ж�
		if(m_SetParamHandle == NULL)
			return -2;//�첽����ʧ��,�����ص�
		return -1;//�첽���ͳɹ�
	}
}
