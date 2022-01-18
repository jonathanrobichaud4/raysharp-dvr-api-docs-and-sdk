#pragma once
#include "ParamBase.h"

class FTP : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;
	
	RSNet_FtpSet_t m_Ftp;
	RSNet_SoleFtpSet_t m_SoleFtp;
};
