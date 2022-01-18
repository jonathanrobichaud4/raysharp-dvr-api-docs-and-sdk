#pragma once
#include "ParamBase.h"

class NetBase : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson();

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_NetworkBaseSet_t m_Net;
	RSNet_IPV6_t m_NetIPv6;
	RSNet_Rtsp_t m_Rstp;
};
