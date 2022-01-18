#pragma once
#include "ParamBase.h"

class DropBoxParam : public CParamBase
{
public:
	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_DropBoxParam_t m_Struct;
};
