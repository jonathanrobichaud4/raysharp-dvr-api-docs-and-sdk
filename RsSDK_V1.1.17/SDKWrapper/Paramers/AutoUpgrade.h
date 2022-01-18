#pragma once
#include "ParamBase.h"

class AutoUpgrade : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);
	
	RSNet_FtpAutoUpgrade_t m_Struct;	
};
