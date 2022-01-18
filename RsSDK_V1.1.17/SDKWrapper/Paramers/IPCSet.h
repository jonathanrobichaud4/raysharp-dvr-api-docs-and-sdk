#pragma once
#include "ParamBase.h"

class IPCSet :public CParamBase
{
public:
	IPCSet(void);
	~IPCSet(void);
	enum
	{
		IPC_ADD = 0,
		IPC_SET,
		IPC_DELETE,
		IPC_REMOTENET
	};

public:
	virtual std::string QueryAll(bool isDefault);//listData
	virtual std::string GetAll();
	virtual std::string QueryAll2();//searchData

	virtual int SaveAll(std::string strData);
	
private:
	int AddIpc(Json::Value obj);
	int ModifyIPCInfo(Json::Value obj);
	int DeleteIpc(Json::Value obj);
	int setRemoteIpcNet(Json::Value obj);
public:
	std::string m_str;
	std::string m_strResult;
	int m_sel;
	int m_type;
	std::vector<RSNet_SoleIPCSet_t> m_vec;
	std::vector<SearchRemDevRep> m_vecEx;
	std::map<std::string,int> m_SearchList;
	RSNet_SoleIPCNetInfo_t m_NetIPC;
};
