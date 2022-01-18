#pragma once
#include "ParamBase.h"

class FishEye:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	
	int SaveAll(std::string strData);
	
	RSNet_FishEye_t m_Struct;	
};