#pragma once
#include "ParamBase.h"

class CSysMaintain : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	RSNet_MaintainSet_t  m_Struct;
};
