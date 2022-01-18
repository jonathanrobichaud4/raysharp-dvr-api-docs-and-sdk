#pragma once
#include "ParamBase.h"

class VideoOutput : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	RSNet_Output_t m_Struct;	
};