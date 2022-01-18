#pragma once
#include "ParamBase.h"

class SXHTTPS : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_HttpsFileParam_t m_Struct;
};
