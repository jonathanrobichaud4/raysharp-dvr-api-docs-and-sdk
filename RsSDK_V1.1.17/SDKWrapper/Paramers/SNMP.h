#pragma once
#include "ParamBase.h"

class SNMP : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_Snmp_t m_Snmp;
};
