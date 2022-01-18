#include "StdAfx.h"
#include "SysParamDst.h"

static void RSNET_CALL StructToXml(void* param, void* userParam)
{
	SysParamDst * pThis = (SysParamDst*)userParam;
	RSNet_GeneralInfoSet_t *nBaseInfo = (RSNet_GeneralInfoSet_t*)param;
}

std::string SysParamDst::QueryAll(bool isDefault)
{
	//请求数据
	std::string strRet = "err";

	RSNetQueryParamParamEx param;
	memset(&param, '\0', sizeof(param));

	memset(&m_DSTSet, '\0', sizeof(RSNet_GeneralInfoSet_t));
	m_DSTSet.StructSize = sizeof(RSNet_GeneralInfoSet_t);
	param.Param = &m_DSTSet;

	param.ParamSize = sizeof(RSNet_GeneralInfoSet_t);
	param.ParamType = MsgParamGeneral;

	if(isDefault)
	{
		if(!RSNetQueryDefaultParamEx(m_pDevice->GetConnection(), &param,MsgDefaultParam))
			return strRet;
	}else{
		if(!RSNetQueryParamEx(m_pDevice->GetConnection(), &param))
			return strRet;
	}

	//处理数据
	//1、m_DSTSet
	m_obj.clear();
	m_obj["TimeMode"] = m_DSTSet.TimeMode;
	m_obj["DateMode"] = m_DSTSet.DateMode;
	m_obj["AutoLogout"] = m_DSTSet.AutoLogout;
	m_obj["Language"] = m_DSTSet.Language;
	m_obj["LanguageMask"] = m_DSTSet.LanguageMask;
	m_obj["VideoFormat"] = m_DSTSet.VideoFormat;
	m_obj["ShowWizard"] = m_DSTSet.ShowWizard;
	m_obj["NtpServAddr"] = (char*)m_DSTSet.NtpServAddr;
	m_obj["vgaresolution"] = m_DSTSet.vgaresolution;
	m_obj["hybirdEnable"] = m_DSTSet.hybirdEnable;
	m_obj["ExtendLanguageMask"] = m_DSTSet.ExtendLanguageMask;
	m_obj["TimeZone_EX"] = m_DSTSet.TimeZone_EX;
	m_obj["WaterMark"] = m_DSTSet.WaterMark;
	m_obj["ClientAutoLogoutTime"] = m_DSTSet.ClientAutoLogoutTime;

		//2、m_DSTSet.DstSet
		Json::Value objDST;
		objDST["Year"] = m_DSTSet.DstSet.time.Year;
		objDST["Month"] = m_DSTSet.DstSet.time.Month;
		objDST["Day"] = m_DSTSet.DstSet.time.Day;
		objDST["Hour"] = m_DSTSet.DstSet.time.Hour;
		objDST["Minute"] = m_DSTSet.DstSet.time.Minute;
		objDST["Second"] = m_DSTSet.DstSet.time.Second;
		objDST["TimeMode"] = m_DSTSet.DstSet.TimeMode;
		objDST["DateMode"] = m_DSTSet.DstSet.DateMode;
		objDST["Dst"] = m_DSTSet.DstSet.Dst;
		objDST["Offset"] = m_DSTSet.DstSet.Offset;
		objDST["DstMode"] = m_DSTSet.DstSet.DstMode;
		objDST["StartMonth"] = m_DSTSet.DstSet.StartMonth;
		objDST["StartWeek"] = m_DSTSet.DstSet.StartWeek;
		objDST["StartWeekDay"] = m_DSTSet.DstSet.StartWeekDay;
		objDST["EndMonth"] = m_DSTSet.DstSet.EndMonth;
		objDST["EndWeek"] = m_DSTSet.DstSet.EndWeek;
		objDST["EndWeekDay"] = m_DSTSet.DstSet.EndWeekDay;
		objDST["StartSecond"] = m_DSTSet.DstSet.StartSecond;
		objDST["EndSecond"] = m_DSTSet.DstSet.EndSecond;

		for (int i=0; i<3; i++)//0 1 2
		{
			objDST["StartDate"].append(m_DSTSet.DstSet.StartDate[i]);
			objDST["StartHour"].append(m_DSTSet.DstSet.StartHour[i]);
			objDST["EndDate"].append(m_DSTSet.DstSet.EndDate[i]);
			objDST["EndHour"].append(m_DSTSet.DstSet.EndHour[i]);
		}
	m_obj["DSTSet"] = objDST;

		//3、m_DSTSet.NtpSet
		Json::Value objNTP;
		objNTP["NtpIPAddr"] = m_DSTSet.NtpSet.NtpIPAddr[0];
		objNTP["UseNtp"] = m_DSTSet.NtpSet.UseNtp;
		objNTP["TimeZone"] = m_DSTSet.NtpSet.TimeZone;
		objNTP["SyncPeriod"] = m_DSTSet.NtpSet.SyncPeriod;
	m_obj["NtpSet"] = objNTP;

	//返回数据
	Json::FastWriter writer;
	strRet = writer.write(m_obj);
	return strRet;
}

int SysParamDst::SaveAll(std::string strData)
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
	//1、m_DSTSet
	m_DSTSet.TimeMode = obj["TimeMode"].asInt();
	m_DSTSet.DateMode = obj["DateMode"].asInt();
	m_DSTSet.AutoLogout = obj["AutoLogout"].asInt();
	m_DSTSet.Language = obj["Language"].asInt();
	m_DSTSet.LanguageMask = obj["LanguageMask"].asInt();
	m_DSTSet.VideoFormat = obj["VideoFormat"].asInt();
	m_DSTSet.ShowWizard = obj["ShowWizard"].asInt();
	
	int maxLen = sizeof(m_DSTSet.NtpServAddr);
	memset(m_DSTSet.NtpServAddr, '\0', maxLen);
	m_str = obj["NtpServAddr"].asString();
	int len = m_str.length() < maxLen ? m_str.length() : maxLen;
	memcpy(m_DSTSet.NtpServAddr, m_str.c_str(), len);
	
	m_DSTSet.vgaresolution = obj["vgaresolution"].asInt();
	m_DSTSet.bIEChangeTime = obj["bIEChangeTime"].asInt();
	m_DSTSet.TimeZone_EX = obj["TimeZone_EX"].asInt();
	m_DSTSet.WaterMark = obj["WaterMark"].asInt();
	m_DSTSet.ClientAutoLogoutTime = obj["ClientAutoLogoutTime"].asInt();

	//2、m_DSTSet.DstSet
	m_DSTSet.DstSet.time.Year = obj["DSTSet"]["Year"].asInt();
	m_DSTSet.DstSet.time.Month = obj["DSTSet"]["Month"].asInt();
	m_DSTSet.DstSet.time.Day = obj["DSTSet"]["Day"].asInt();
	m_DSTSet.DstSet.time.Hour = obj["DSTSet"]["Hour"].asInt();
	m_DSTSet.DstSet.time.Minute = obj["DSTSet"]["Minute"].asInt();
	m_DSTSet.DstSet.time.Second = obj["DSTSet"]["Second"].asInt();
	m_DSTSet.DstSet.TimeMode = obj["DSTSet"]["TimeMode"].asInt();
	m_DSTSet.DstSet.DateMode = obj["DSTSet"]["DateMode"].asInt();
	m_DSTSet.DstSet.Dst = obj["DSTSet"]["Dst"].asInt();
	m_DSTSet.DstSet.Offset = obj["DSTSet"]["Offset"].asInt();
	m_DSTSet.DstSet.DstMode = obj["DSTSet"]["DstMode"].asInt();
	m_DSTSet.DstSet.StartMonth = obj["DSTSet"]["StartMonth"].asInt();
	m_DSTSet.DstSet.StartWeek = obj["DSTSet"]["StartWeek"].asInt();
	m_DSTSet.DstSet.StartWeekDay = obj["DSTSet"]["StartWeekDay"].asInt();
	m_DSTSet.DstSet.EndMonth = obj["DSTSet"]["EndMonth"].asInt();
	m_DSTSet.DstSet.EndWeek = obj["DSTSet"]["EndWeek"].asInt();
	m_DSTSet.DstSet.EndWeekDay = obj["DSTSet"]["EndWeekDay"].asInt();
	m_DSTSet.DstSet.StartSecond = obj["DSTSet"]["StartSecond"].asInt();
	m_DSTSet.DstSet.EndSecond = obj["DSTSet"]["EndSecond"].asInt();
	m_DSTSet.DstSet.StructSize = sizeof(RSNet_DSTSet_t);

	int tmp1,tmp2;
	for(int i=0; i<3; i++)//0 1 2
	{
		tmp1 = obj["DSTSet"]["StartDate"][i].asInt();//年月日
		if(tmp1>255)
			tmp1 -= 2000;
		m_DSTSet.DstSet.StartDate[i] = tmp1;

		tmp2 = obj["DSTSet"]["EndDate"][i].asInt();//年月日
		if(tmp2>255)
			tmp2 -= 2000;
		m_DSTSet.DstSet.EndDate[i] = tmp2;
	}

	for(int i=0; i<3; i++)//0 1 2
	{
		m_DSTSet.DstSet.StartHour[i] = obj["DSTSet"]["StartHour"][i].asInt();//时分秒
		m_DSTSet.DstSet.EndHour[i] = obj["DSTSet"]["EndHour"][i].asInt();//时分秒
	}
	
	//3、m_DSTSet.NtpSet
	m_DSTSet.NtpSet.NtpIPAddr[0] = obj["NtpSet"]["NtpIPAddr"].asInt();
	m_DSTSet.NtpSet.UseNtp = obj["NtpSet"]["UseNtp"].asInt();
	m_DSTSet.NtpSet.TimeZone = obj["NtpSet"]["TimeZone"].asInt();
	m_DSTSet.NtpSet.SyncPeriod = obj["NtpSet"]["SyncPeriod"].asInt();
	m_DSTSet.NtpSet.StructSize = sizeof(RSNet_NtpSet_t);

	//保存数据
	RSNetSetParamParam param;
	memset(&param, '\0', sizeof(param));
	param.ParamType = MsgParamGeneral;
	param.Param = &m_DSTSet;
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