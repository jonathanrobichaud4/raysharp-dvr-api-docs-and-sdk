#pragma once
#include "ParamBase.h"

class NetVPN : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_OpenVpnParam_t m_VPN;
};
