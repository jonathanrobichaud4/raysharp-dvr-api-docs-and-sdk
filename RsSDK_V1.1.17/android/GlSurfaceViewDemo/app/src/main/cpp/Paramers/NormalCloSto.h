#pragma once
#include "ParamBase.h"

class NormalCloSto : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;

	RSNet_NormalCloudStorageInfo_t m_Struct;
};
