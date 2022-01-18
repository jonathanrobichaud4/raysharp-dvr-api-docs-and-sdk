#pragma once
#include "ParamBase.h"

class LensShade:public CParamBase
{
public:
	LensShade(void);

	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int AlarmOutNum;
	int SaveAll(std::string strData);

	std::vector< RSNet_SoleODParam_t> m_vec;
};
