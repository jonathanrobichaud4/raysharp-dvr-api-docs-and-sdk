#pragma once
#include "ParamBase.h"

class FtpPlan : public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	
	std::vector<RSNet_SoleFtpScheduleset_t> m_vec;	
};
