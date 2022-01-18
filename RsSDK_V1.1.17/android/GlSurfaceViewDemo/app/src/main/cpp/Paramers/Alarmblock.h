#pragma once
#include "ParamBase.h"

class AlarmBlock:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	
	int SaveAll(std::string strData);
	
	RSNet_OcclusionSet_t m_Struct;	
};