#pragma once
#include "ParamBase.h"

class ALTEReport : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;

	RSNet_ALTEReport_t m_Report;
};
