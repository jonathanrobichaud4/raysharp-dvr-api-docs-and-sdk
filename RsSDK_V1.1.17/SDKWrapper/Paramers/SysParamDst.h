#pragma once
#include "ParamBase.h"

class SysParamDst : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	RSNet_GeneralInfoSet_t m_DSTSet;
};
