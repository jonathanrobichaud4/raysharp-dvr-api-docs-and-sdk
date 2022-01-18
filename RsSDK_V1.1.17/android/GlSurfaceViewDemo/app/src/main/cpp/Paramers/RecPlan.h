#pragma once
#include "ParamBase.h"

class RecPlan : public CParamBase
{
public:
	RecPlan(void);
	bool bSmart;

	std::string QueryAll(bool bDefault);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	
	std::vector<RSNet_SoleScheduleSet_t> m_vec;	
};
