#pragma once
#include "ParamBase.h"

class IPFilterList : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson();

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_NetworkIPFilter_t m_IPFilter;
};
