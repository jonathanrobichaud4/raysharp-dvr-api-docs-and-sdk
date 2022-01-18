#pragma once
#include "ParamBase.h"

class PlatformSet : public CParamBase
{
public:
	PlatformSet(void);
	~PlatformSet(void);

	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string xml);
	std::string m_str;
private:
	RSNet_PlatformSet_t m_Struct;
};
