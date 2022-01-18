#pragma once
#include "ParamBase.h"

class IEEEX : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_Ieee8021xParam_t m_IeeeX;
};
