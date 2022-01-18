#pragma once
#include "ParamBase.h"

class SSL : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_HttpsParam_t m_SSL;
};
