#pragma once
#include "ParamBase.h"

class AnalogCh : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string xml);
	std::vector<RSNet_SoleAnalogCam_t> m_vec;
};
