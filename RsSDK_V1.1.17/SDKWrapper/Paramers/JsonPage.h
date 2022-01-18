#pragma once
#include "ParamBase.h"

class JsonPage : public CParamBase
{
public:
	JsonPage(){
		m_SetParamHandle = NULL;
		m_QueryParamHandle = NULL;
	}
	std::string QueryAll(std::string strData);

	int SaveAll(std::string strData);

	std::string m_str;
	std::string m_Net;
	RSSetParamJson m_SetParamHandle;
	RSQueryParamJson m_QueryParamHandle;
};
