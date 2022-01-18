#pragma once
#include "ParamBase.h"

class ZeroChannel : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	RSNet_ZeroChnSet_t m_Struct;	
};