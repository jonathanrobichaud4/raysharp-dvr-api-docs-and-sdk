#pragma once
#include "ParamBase.h"

class NetFilter : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;

	RSNet_NetFilter_t m_Filter;
};
