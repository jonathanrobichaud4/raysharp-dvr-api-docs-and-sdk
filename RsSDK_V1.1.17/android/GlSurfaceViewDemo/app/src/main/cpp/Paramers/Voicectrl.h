#pragma once
#include "ParamBase.h"

class VoiceCtrl : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	RSNet_VoiceSet_t m_Struct;	
};