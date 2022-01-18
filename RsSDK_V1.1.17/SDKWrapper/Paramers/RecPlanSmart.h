#pragma once
#include "ParamBase.h"

class RecPlanSmart : public CParamBase
{
public:
	RecPlanSmart(void);
	bool bSmart;

	std::string QueryAll(bool bDefault);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	
	std::vector<RSNet_SoleIntelliRecSchedule_t> m_vec;	
};
