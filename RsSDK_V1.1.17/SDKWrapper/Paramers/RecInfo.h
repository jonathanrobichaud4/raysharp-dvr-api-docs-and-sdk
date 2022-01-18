#pragma once
#include "ParamBase.h"

class RecInfo :public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	std::vector<RSNet_SoleRecInfo_t> m_vec;
};
