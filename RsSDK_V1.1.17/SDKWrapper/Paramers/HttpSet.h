#pragma once
#include "ParamBase.h"

class HttpSet : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson();

	int SaveAll(std::string strData);

	RSNet_UrmetHttpParam_t m_HttpSet;
	std::string m_str;
};
