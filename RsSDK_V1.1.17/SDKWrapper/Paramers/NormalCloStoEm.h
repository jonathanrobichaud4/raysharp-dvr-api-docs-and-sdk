#pragma once
#include "ParamBase.h"

class NormalCloStoEm : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string xml);
	std::string m_str;

	RSNet_NormalCloudStorageEmail_t m_Struct;
};
