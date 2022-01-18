#pragma once
#include "ParamBase.h"

class NetDNS : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	
	int SaveAll(std::string strData);
	
	std::string m_str;

	RSNet_DDNSSet_t m_DDNSSet;
};
