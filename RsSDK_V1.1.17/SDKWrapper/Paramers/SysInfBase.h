#pragma once
#include "ParamBase.h"

class CSysInfBase:public CParamBase
{
public:
	CSysInfBase()
	{
		m_bQueryExParam = false;
	}
	std::string QueryAll(std::string strData);
	void StructToJson();

	int SaveAll(std::string strData);

	RSNet_SystemBaseInfo_t m_BaseInfo;
	RSNet_SysParamInfoEx_t m_BaseInfoEx;
	std::string m_str;
	bool m_bQueryExParam;
};
