#include "StdAfx.h"
#include "ALTEReport.h"

std::string ALTEReport::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Report, '\0', sizeof(RSNet_ALTEReport_t));
	m_Report.structsize = sizeof(RSNet_ALTEReport_t);
	param.Param = &m_Report;

	param.ParamSize = sizeof(RSNet_ALTEReport_t);
	param.ParamType = MsgParamALTEReport;

	if (!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
		return strRet;

	//处理数据
	m_obj.clear();
	m_obj["ReportIpAddr1"] = m_Report.ReportIpAddr1;
	m_obj["ReportIpAddr2"] = m_Report.ReportIpAddr2;
	m_obj["Port1"] = m_Report.Port1;
	m_obj["Port2"] = m_Report.Port2;
	m_obj["ReportTypeMask"] = m_Report.ReportTypeMask;
	m_obj["ReportType"] = m_Report.ReportType;
	m_obj["ReportPeriod"] = m_Report.ReportPeriod;
	m_obj["EnableReport"] = m_Report.EnableReport;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int ALTEReport::SaveAll(std::string strData)
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
		m_Report.EnableReport = obj["EnableReport"].asUInt();

		int maxLen = sizeof(m_Report.ReportIpAddr1);
		memset(m_Report.ReportIpAddr1, '\0', maxLen);
		m_str = obj["ReportIpAddr1"].asString();
		int len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Report.ReportIpAddr1, m_str.c_str(), len);

		maxLen = sizeof(m_Report.ReportIpAddr2);
		memset(m_Report.ReportIpAddr2, '\0', maxLen);
		m_str = obj["ReportIpAddr2"].asString();
		len = m_str.length() < maxLen ? m_str.length() : maxLen;
		memcpy(m_Report.ReportIpAddr2, m_str.c_str(), len);

		m_Report.Port1 = obj["Port1"].asUInt();
		m_Report.Port2 = obj["Port2"].asUInt();
		m_Report.ReportPeriod = obj["ReportPeriod"].asUInt();

		//m_Report.ReportTypeMask = obj["ReportTypeMask"].asUInt();
		m_Report.ReportType = obj["ReportType"].asUInt();
		m_Report.structsize = sizeof(RSNet_ALTEReport_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));

	param.ParamType = MsgParamALTEReport;
	param.Param = &m_Report;

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