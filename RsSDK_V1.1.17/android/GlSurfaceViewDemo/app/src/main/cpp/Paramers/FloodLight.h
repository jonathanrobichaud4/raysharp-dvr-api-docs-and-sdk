#pragma once
#include "ParamBase.h"

class FloodLight: public CParamBase
{
public:
	FloodLight(void);

	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector< RSNet_SoleFloodLightSet_t> m_vec;
};
