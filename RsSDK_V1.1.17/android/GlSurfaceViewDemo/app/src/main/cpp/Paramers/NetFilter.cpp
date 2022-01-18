#include "StdAfx.h"
#include "NetFilter.h"

std::string NetFilter::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Filter, '\0', sizeof(RSNet_NetFilter_t));
	m_Filter.structsize = sizeof(RSNet_NetFilter_t);
	param.Param = &m_Filter;

	param.ParamSize = sizeof(RSNet_NetFilter_t);
	param.ParamType = MsgParamNetFilter;

	if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["FilterEnable"] = m_Filter.FilterEnable;
	m_obj["FilterMode"] = m_Filter.FilterMode;
	int NUM = m_Filter.RuleCnt;
	m_obj["RowNum"] = NUM;
	
		Json::Value RowsData(Json::arrayValue);
		for(int i=0; i<NUM; i++)
		{
			Json::Value oneRowData(Json::objectValue);
			oneRowData["Type"] = m_Filter.RuleMode[i];

			Json::Value arrAddr(Json::arrayValue);
			for(int j=0; j<8; j++)
			{
				arrAddr.append(m_Filter.RuleAddr[i][j]);
			}
			oneRowData["AddressArr"] = arrAddr;

			RowsData.append(oneRowData);
		}
	m_obj["RowsData"] = RowsData;


	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int NetFilter::SaveAll(std::string strData)
{
	if(strData == "null"){
		return false;
	}

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return false;
	}

	/*
	{
		"FilterEnable":1,
		"FilterMode":1,
		"RowsData":[
			{"AddressArr":[37,126,222,225,0,0,0,0],"Type":0,"index":0,"Address":"37.126.222.225"},
			{"AddressArr":[0,204,109,232,68,153,0,0],"Type":1,"index":1,"Address":"0-cc-6d-e8-44-99"},
			{"AddressArr":[0,0,0,0,0,0,0,0],"Type":1,"index":2,"Address":"0-0-0-0-0-0"},
			{"AddressArr":[192,168,11,122,0,0,0,0],"Type":0,"index":3,"Address":"192.168.11.122"}
		]
	}
	*/

	//处理数据
		m_Filter.FilterEnable = obj["FilterEnable"].asUInt();	
		m_Filter.FilterMode = obj["FilterMode"].asUInt();	
		int nLen = obj["RowsData"].size();
		m_Filter.RuleCnt = nLen;

		for(int i=0; i<nLen; i++)//每条数据
		{
			m_Filter.RuleMode[i] = obj["RowsData"][i]["Type"].asUInt();

			for(int j=0; j<8; j++)
			{
				m_Filter.RuleAddr[i][j] = obj["RowsData"][i]["AddressArr"][j].asUInt();
			}
		}

		m_Filter.structsize = sizeof(RSNet_NetFilter_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));

	param.ParamType = MsgParamNetFilter;
	param.Param = &m_Filter;

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