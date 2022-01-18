#pragma once
#include "ParamBase.h"

class Devlog : public CParamBase
{
public:
	Devlog(void);
	~Devlog(void);
public:
	static void RSNET_CALL RSSearchLogCallback(void* data, unsigned int size, void* userParam);
	int SearchLogProc(void* data,unsigned int size);
	std::string QueryAll(std::string strData);
private:
	int m_TotalNum ;
	int m_StructSize;
	unsigned char* m_pData;

	LogSearchInput_t m_Req;
};
