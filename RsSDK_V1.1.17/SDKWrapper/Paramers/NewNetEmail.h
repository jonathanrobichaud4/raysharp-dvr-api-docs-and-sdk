#pragma once
#include "ParamBase.h"

class NewNetEmail : public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	void StructToJson();
	
	int SaveAll(std::string strData);

	std::string m_str;
	RSNet_NewEmailSet_t m_EmailSet;
};
