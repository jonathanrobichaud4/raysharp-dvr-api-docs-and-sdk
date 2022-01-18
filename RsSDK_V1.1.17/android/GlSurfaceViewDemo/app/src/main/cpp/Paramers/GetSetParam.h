#pragma once
#include "ParamBase.h"

class CGetSetParam:public CParamBase
{
public:
	CGetSetParam(void);
	~CGetSetParam(void);
public:
	int ExpParam(void* data,UINT size);
	std::string QueryAll(std::string strData);

	int SaveAll(std::string strData);
	RemoteNewParamBackupResp_t* m_SoleParam;
};
