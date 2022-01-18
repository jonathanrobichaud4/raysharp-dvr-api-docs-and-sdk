#pragma once
#include "ParamBase.h"

class SysInfHdd : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);
	
	int SaveAll(std::string strData);

	RSNet_HddInfo_t m_HddInfo;
	std::vector<RSNet_SoleHddInfo_t> m_vec;
};
