#pragma once
#include "ParamBase.h"

class Defaultparam : public CParamBase
{
public:
	int SaveAll(std::string strData);
	
	RSNet_DefaultSet_t m_Def;
};
