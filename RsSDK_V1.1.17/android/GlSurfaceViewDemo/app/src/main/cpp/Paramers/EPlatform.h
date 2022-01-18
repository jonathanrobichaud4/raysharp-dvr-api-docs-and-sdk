#pragma once
#include "ParamBase.h"

class EPlatform : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	Eplateform_t m_eplatform;
};
