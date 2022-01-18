#pragma once
#include "ParamBase.h"


class SysParamSerial:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	int SaveAll(std::string strData);

	RSNet_SerialInfo_t m_SerialInfo;	
};
