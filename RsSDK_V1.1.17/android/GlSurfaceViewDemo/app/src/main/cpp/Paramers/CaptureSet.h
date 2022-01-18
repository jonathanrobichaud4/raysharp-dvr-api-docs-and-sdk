#pragma once
#include "ParamBase.h"

class CaptureSet : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector<RSNet_SoleCaptureSet_t> m_vec;
};