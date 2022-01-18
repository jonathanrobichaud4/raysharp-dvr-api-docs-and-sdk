#pragma once
#include "ParamBase.h"

class SendCertificate:public CParamBase
{
public:
	SendCertificate(void);
	~SendCertificate(void);
public:

	int SaveAll(std::string strData);
	RSNet_CertificatesParam_t m_SoleParam;
};
