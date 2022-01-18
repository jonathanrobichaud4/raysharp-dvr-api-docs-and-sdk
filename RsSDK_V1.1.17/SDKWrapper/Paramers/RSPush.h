#pragma once
#include "ParamBase.h"

class RSPush :public CParamBase
{
public:
	RSPush(void);
	~RSPush(void);

public:
	virtual int SaveAll(std::string strData);
	
private:

};
