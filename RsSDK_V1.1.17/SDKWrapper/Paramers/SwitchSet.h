#pragma once
#include "ParamBase.h"

class SwitchSet : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	RSNet_SwitchSet_t m_Struct;	
};