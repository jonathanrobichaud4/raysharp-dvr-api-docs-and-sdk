#pragma once
#include "ParamBase.h"

class IntelligentPlan : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector <RSNet_SoleScheduleSet_t> m_vec;	
};