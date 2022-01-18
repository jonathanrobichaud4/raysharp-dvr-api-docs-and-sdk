#pragma once
#include "ParamBase.h"

class AlarmPlan :	public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	std::vector <RSNetNew_SoleAlarmOutScheduleset_t> m_vec;	
};
