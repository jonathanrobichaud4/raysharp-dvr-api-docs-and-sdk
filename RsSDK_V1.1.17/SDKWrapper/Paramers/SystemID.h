#pragma once
#include "ParamBase.h"

class CSystemID:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	
	int SaveAll(std::string xml);

	RSNet_SystemIDCtrl_t m_Struct;
};
