#pragma once
#include "ParamBase.h"

#define AlarmMaxNum 6

class AlarmAbnormity:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);
	int AlarmOutNum;

	int SaveAll(std::string strData);

	RSNet_SoleAbnormalSet_t listParam[AlarmMaxNum];	
};
