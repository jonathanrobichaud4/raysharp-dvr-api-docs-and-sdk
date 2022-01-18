#pragma once
#include "ParamBase.h"

class SwannWifi : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	RSNet_CountryCode_t m_Wifiset;
	std::string m_str;
};
