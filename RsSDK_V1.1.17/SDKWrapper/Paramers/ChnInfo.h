#pragma once
#include "ParamBase.h"

class ChnInfo :public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	std::vector<RSNet_SoleChnInfo_t> m_vec;
};
