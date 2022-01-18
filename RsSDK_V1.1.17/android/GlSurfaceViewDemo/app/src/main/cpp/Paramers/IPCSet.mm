#include "StdAfx.h"
#include "IPCSet.h"

IPCSet::IPCSet(void)
{
	m_sel = -1;
	m_type = -1;
	m_strResult = "err";
}

IPCSet::~IPCSet(void)
{
}

static void RSNET_CALL ListParamCallback(void* data, void* userParam)
{
	IPCSet* pThis = (IPCSet*)userParam;
	RSNet_SoleIPCSet_t* SoleIPCSet = (RSNet_SoleIPCSet_t*)data;
	pThis->m_vec.push_back(*SoleIPCSet);
}

static void RSNET_CALL SearchListParamCallback(void* data, void* userParam)
{
	IPCSet* pThis = (IPCSet*)userParam;
	SearchRemDevRep* SoleIPCSet = (SearchRemDevRep*)data;
	pThis->m_vecEx.push_back(*SoleIPCSet);
}

//listData 获取所有行数据
std::string IPCSet::QueryAll(bool isDefault)
{
	RSNetQueryParamParam param;
	memset(&param, '\0', sizeof(param));

	m_vec.clear();

	ChannelParamReq req;
	TransformChannelParamReq_All(&req);

	param.ParamType = MsgParamIpc;
	param.Req = &req;

	param.ListParamSize = sizeof(RSNet_SoleIPCSet_t);
	param.ListParamCallback = ListParamCallback;

	param.UserParam = this;

	if (!RSNetQueryParam(m_pDevice->GetConnection(), &param))
	{
		m_strResult = "err";
		return m_strResult;
	}

	return GetAll();
}


//获取 暂存于插件的listData (因为有修改)
std::string IPCSet::GetAll()
{
	std::string str,strTemple;
	std::string strIP;

	int i = 0;
	m_SearchList.clear();

	Json::Value root(Json::arrayValue);
	for (i=0; i<m_vec.size(); ++i)
	{
		Json::Value obj(Json::objectValue);
		obj["ch"] = i;

		obj["IP0"] = m_vec[i].IPAddr[0];
		obj["IP1"] = m_vec[i].IPAddr[1];
		obj["IP2"] = m_vec[i].IPAddr[2];
		obj["IP3"] = m_vec[i].IPAddr[3];

		obj["Port"] = m_vec[i].Port;

		//std::string UserName((char*)m_vec[i].UserName);
		//obj["UserName"] = UserName;
		obj["UserName"] = (char*)m_vec[i].UserName;
		obj["UserPW"] = (char*)m_vec[i].UserPW;

		obj["ChnNo"] = m_vec[i].ChnNo;
		obj["Protocol"] = m_vec[i].Protocol;
		obj["Enable"] = m_vec[i].Enable;
		obj["ChnMax"] = m_vec[i].ChnMax;
		obj["IPChnStatus"] = m_vec[i].IPChnStatus;
		obj["Version"] = m_vec[i].Version;
		obj["switchmode"] = m_vec[i].switchmode;

		int u64devType_Low = m_vec[i].u64devType & 0xffffffff;
		int u64devType_High = m_vec[i].u64devType >> 32; 
		obj["u64devType_Low"] = u64devType_Low;
		obj["u64devType_High"] = u64devType_High;

		obj["macAddr"] = (char*)m_vec[i].macAddr;
		for(int j = 0;j < 4;++j)
		{
			obj["GateWay"][j] = m_vec[i].GateWay[j];
			obj["dns1"][j] = m_vec[i].dns1[j];
			obj["dns2"][j] = m_vec[i].dns2[j];
		}
		obj["IEport"] = m_vec[i].IEport;
		obj["IpcName"] = (char*)m_vec[i].IpcName;
		obj["DevType2"] = (char*)m_vec[i].DevType;
		obj["Manufacturer"] = (char*)m_vec[i].Manufacturer;
#if defined(RS_IPHONE)||defined(RS_ANDROID)
#else
		obj["SoftVersion"] = (char*)m_vec[i].SoftVersion;
#endif

		char bufMask[256] = {0};
		sprintf(bufMask, "%u.%u.%u.%u", m_vec[i].mask[0],m_vec[i].mask[1],m_vec[i].mask[2],m_vec[i].mask[3]);
		obj["mask"] = bufMask;

		obj["DevAlias"] = (char*)m_vec[i].DevAlias;
		obj["AliasPos"] = m_vec[i].AliasPos;
		obj["sIPAddr"] = (char*)m_vec[i].sIPAddr;
		obj["P2pUID"] = (char*)m_vec[i].P2pUID;
		obj["poeflag"] = m_vec[i].poeflag;

		root.append(obj);

		char strChar[256];
		memset(strChar, '\0', sizeof(strChar));
		sprintf(strChar,"%u.%u.%u.%u:%u",m_vec[i].IPAddr[0],m_vec[i].IPAddr[1],m_vec[i].IPAddr[2],m_vec[i].IPAddr[3],m_vec[i].Port);
		std::string strIP(strChar);
		if (m_vec[i].Enable)
		{
			m_SearchList.insert( std::pair<std::string,int>(strIP,1) );
		}
	}

	Json::FastWriter writer;
	m_strResult =  writer.write(root);
	return m_strResult;
}

//searchData 获取所有行数据
std::string IPCSet::QueryAll2()
{
	SearchRemDevReq Req = {0};
	LoginRsp* logRsp = m_pDevice->GetLoginRsp();
	Req.UserKey = logRsp->UserKey;
	RSNetQueryTemporaryParamParam param;
	memset(&param, '\0', sizeof(param));
    m_vecEx.clear();

	param.ParamMainType = MsgSearchRemoteDev;
	param.ParamSize = sizeof(SearchRemDevReq);
	param.Req = &Req;
	param.UserParam = this;
	param.ListParamSize = sizeof(SearchRemDevRep);
	param.ListParamCallback = SearchListParamCallback;

	std::string strTemple;
	if(!RSNetQueryTemporaryParam(m_pDevice->GetConnection(),&param))
	{
		m_strResult = "err";
		return m_strResult;
	}

	Json::Value root(Json::arrayValue);
	if(m_vecEx.size()==1 && m_vecEx[0].IPAddr[0]==0)
	{	
		Json::FastWriter writer;
		return writer.write(root).c_str();
	}

	for (int i=0; i<m_vecEx.size(); ++i)
	{
		//list里已经有该IP、端口了，就continue

		char strChar[256];
		sprintf(strChar,"%u.%u.%u.%u:%u",m_vecEx[i].IPAddr[0],m_vecEx[i].IPAddr[1],m_vecEx[i].IPAddr[2],m_vecEx[i].IPAddr[3],m_vecEx[i].Port);
		std::string strIP(strChar);
		
		std::map<std::string,int>::iterator iter;
		iter = m_SearchList.find(strIP);
		if (iter!=m_SearchList.end())//找到了
		{
			continue;
		}

		if (strncmp((char *)m_vecEx[i].DevType,"NVR",3) == 0)
		{
			continue;
		}

		Json::Value obj(Json::objectValue);
		
		char bufIP[256] = {0};
		sprintf(bufIP, "%u.%u.%u.%u", m_vecEx[i].IPAddr[0],m_vecEx[i].IPAddr[1],m_vecEx[i].IPAddr[2],m_vecEx[i].IPAddr[3]);
		obj["IPAddr"] = bufIP;

		obj["port"] = m_vecEx[i].Port;
		obj["manufacturer"] = m_vecEx[i].manufacturer;
		obj["devtype"] = m_vecEx[i].devicetype;
		obj["Protocol"] = m_vecEx[i].Protocol;
		obj["chnmax"] = m_vecEx[i].ChnMax;

		obj["MacAddr"] = (char*)m_vecEx[i].MacAddr;

		Json::Value arrValue;
		for(int j=0; j<8; j++) {
			arrValue.append(m_vecEx[i].MulChannel[j]);
		}
		obj["MulChannel"] = arrValue;

		obj["softversion"] = m_vecEx[i].software;

		obj["WebPort"] = m_vecEx[i].WebPort;
		obj["DevTypeULLlo"] = (int)m_vecEx[i].DevTypeULL;
		obj["DevTypeULLhi"] = (int)(m_vecEx[i].DevTypeULL>>32);
		for(int j = 0;j < 4;++j)
		{
			obj["Dns1"][j] = m_vecEx[i].Dns1[j];
			obj["Dns2"][j] = m_vecEx[i].Dns2[j];
			obj["Netmask"][j] = m_vecEx[i].Netmask[j];
			obj["GateWay"][j] = m_vecEx[i].GateWay[j];
		}
		obj["Dns1_0"] = m_vecEx[i].Dns1[0];
		obj["Dns1_1"] = m_vecEx[i].Dns1[1];
		obj["Dns1_2"] = m_vecEx[i].Dns1[2];
		obj["Dns1_3"] = m_vecEx[i].Dns1[3];

		obj["Dns2_0"] = m_vecEx[i].Dns2[0];
		obj["Dns2_1"] = m_vecEx[i].Dns2[1];
		obj["Dns2_2"] = m_vecEx[i].Dns2[2];
		obj["Dns2_3"] = m_vecEx[i].Dns2[3];

		obj["Netmask_0"] = m_vecEx[i].Netmask[0];
		obj["Netmask_1"] = m_vecEx[i].Netmask[1];
		obj["Netmask_2"] = m_vecEx[i].Netmask[2];
		obj["Netmask_3"] = m_vecEx[i].Netmask[3];

		obj["GateWay_0"] = m_vecEx[i].GateWay[0];
		obj["GateWay_1"] = m_vecEx[i].GateWay[1];
		obj["GateWay_2"] = m_vecEx[i].GateWay[2];
		obj["GateWay_3"] = m_vecEx[i].GateWay[3];

		obj["UserName"] = (char*)m_vecEx[i].UserName;
		obj["UserPW"] = (char*)m_vecEx[i].UserPW;

		obj["Version"] = m_vecEx[i].Version;
		obj["hardware"] = m_vecEx[i].hardware;
		obj["switchflag"] = m_vecEx[i].switchflag;
		obj["portnum"] = m_vecEx[i].portnum;
		obj["switchmode"] = m_vecEx[i].switchmode;
		root.append(obj);
	}

	Json::FastWriter writer;
	return writer.write(root);
}


int IPCSet::SaveAll(std::string strData)
{
	Json::Reader reader;
	Json::Value root(Json::objectValue);

	if(!reader.parse(strData, root))
		return false;

	int type = root["type"].asInt();
	Json::Value data = root["data"];

	if(type == IPC_ADD)
	{
		return AddIpc(data);
	}
	else if(type == IPC_SET)
	{
		return ModifyIPCInfo(data);
	}
	else if(type == IPC_DELETE)
	{
		return DeleteIpc(data);
	}
	else if(type == IPC_REMOTENET)
	{
		return setRemoteIpcNet(data);
	}

	return false;
}

//把勾选的行，保存到板端、暂存插件
int IPCSet::AddIpc(Json::Value obj)
{
	int count = obj.size();
	int len = m_vec.size();
	if (!(count>=1 && count <=len))
	{
		return false;
	}

	std::vector<RSNet_SoleIPCSet_t> vecAdd;
	for(int i=0; i<count; i++)
	{
		int sel = obj[i]["boundchannel"].asInt();

		m_str = obj[i]["ip"].asString();
		memset(m_vec[sel].sIPAddr, '\0', sizeof(m_vec[sel].sIPAddr));
		int len = m_str.length() < sizeof(m_vec[sel].sIPAddr) ? m_str.length() : sizeof(m_vec[sel].sIPAddr);
		memcpy(m_vec[sel].sIPAddr, m_str.c_str(), len);

		m_vec[sel].Port = obj[i]["port"].asUInt();
		m_vec[sel].Protocol = obj[i]["protocol"].asInt();

		m_str = obj[i]["username"].asString();
		memset(m_vec[sel].UserName, '\0', MaxNameLen);
		len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
		memcpy(m_vec[sel].UserName, m_str.c_str(), len);


		m_str = obj[i]["password"].asString();
		memset(m_vec[sel].UserPW, '\0', MaxNameLen);
		len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
		memcpy(m_vec[sel].UserPW,m_str.c_str(),len);

		if(!obj[i]["manufacturer"].isNull())
		{
			m_str = obj[i]["manufacturer"].asString();
			memset(m_vec[sel].Manufacturer, '\0', MaxNameLen);
			len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
			memcpy(m_vec[sel].Manufacturer,m_str.c_str(),len);
		}

		if(!obj[i]["mac"].isNull())
		{
			m_str = obj[i]["mac"].asString();
			memset(m_vec[sel].macAddr, '\0', MaxNameLen);
			len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
			memcpy(m_vec[sel].macAddr,m_str.c_str(),len);
		}

		if(!obj[i]["softversion"].isNull())
		{
			m_str = obj[i]["softversion"].asString();
			memset(m_vec[sel].SoftVersion, '\0', MaxNameLen);
			len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
			memcpy(m_vec[sel].SoftVersion,m_str.c_str(),len);
		}

		if(!obj[i]["devtype"].isNull())
		{
			m_str = obj[i]["devtype"].asString();
			memset(m_vec[sel].DevType, '\0', MaxNameLen);
			len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
			memcpy(m_vec[sel].DevType,m_str.c_str(),len);
		}

		if(!obj[i]["chnmax"].isNull())
			m_vec[sel].ChnMax = obj[i]["chnmax"].asUInt();

		if(!obj[i]["WebPort"].isNull())
			m_vec[sel].IEport = obj[i]["WebPort"].asUInt();

		if(!obj[i]["Dns1_0"].isNull())
		{
			m_vec[sel].dns1[0] = obj[i]["Dns1_0"].asUInt();
			m_vec[sel].dns1[1] = obj[i]["Dns1_1"].asUInt();
			m_vec[sel].dns1[2] = obj[i]["Dns1_2"].asUInt();
			m_vec[sel].dns1[3] = obj[i]["Dns1_3"].asUInt();
		}

		if(!obj[i]["Dns2_0"].isNull())
		{
			m_vec[sel].dns2[0] = obj[i]["Dns2_0"].asUInt();
			m_vec[sel].dns2[1] = obj[i]["Dns2_1"].asUInt();
			m_vec[sel].dns2[2] = obj[i]["Dns2_2"].asUInt();
			m_vec[sel].dns2[3] = obj[i]["Dns2_3"].asUInt();
		}

		if(!obj[i]["Netmask_0"].isNull())
		{
			m_vec[sel].mask[0] = obj[i]["mask_0"].asUInt();
			m_vec[sel].mask[1] = obj[i]["mask_1"].asUInt();
			m_vec[sel].mask[2] = obj[i]["mask_2"].asUInt();
			m_vec[sel].mask[3] = obj[i]["mask_3"].asUInt();
		}

		if(!obj[i]["GateWay_0"].isNull())
		{
			m_vec[sel].GateWay[0] = obj[i]["GateWay_0"].asUInt();
			m_vec[sel].GateWay[1] = obj[i]["GateWay_1"].asUInt();
			m_vec[sel].GateWay[2] = obj[i]["GateWay_2"].asUInt();
			m_vec[sel].GateWay[3] = obj[i]["GateWay_3"].asUInt();
		}
		
		UINT  lo, hi;
		if((!obj[i]["DevTypeULLhi"].isNull()) && (!obj[i]["DevTypeULLlo"].isNull()))
		{
			hi = obj[i]["DevTypeULLhi"].asUInt();
			lo = obj[i]["DevTypeULLlo"].asUInt();
			m_vec[sel].u64devType = (((unsigned long long)hi)<<32) | ((unsigned long long)lo & 0xffffffff);
		}

		if(!obj[i]["Version"].isNull())
			m_vec[sel].Version = obj[i]["Version"].asUInt();

		if(!obj[i]["switchflag"].isNull())
			m_vec[sel].switchflag = obj[i]["switchflag"].asUInt();

		if(!obj[i]["portnum"].isNull())
			m_vec[sel].portnum = obj[i]["portnum"].asUInt();

		if(!obj[i]["MulChannel"].isNull()){
			for(int j=0; j<8; ++j)
			{
				m_vec[sel].MulChannel[j] = obj[i]["MulChannel"][j].asInt();
			}
		}
		if(!obj[i]["Enable"].isNull()){
			m_vec[sel].Enable = obj[i]["Enable"].asInt();
		}else{
			m_vec[sel].Enable = 1;
		}
		if(sel < 32)
		{
			m_vec[sel].ChannelMask = 1 << sel;
		}
		else
		{
			m_vec[sel].ChannelMask = 0xFFFF0000 + sel;
		}
		m_vec[sel].StructSize = sizeof(RSNet_SoleIPCSet_t);

		vecAdd.push_back(m_vec[sel]);
	}

	
	RSNetSetParamParam param;
	memset(&param, '\0',  sizeof(param));
	param.ParamType = MsgParamIpc;
	param.ListParams = &vecAdd[0];
	param.ListParamNum = vecAdd.size();
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}

int IPCSet::ModifyIPCInfo(Json::Value obj)
{
	int sel = obj["boundchannel"].asInt();

	if (!(sel>=0 && sel<m_vec.size()))
	{
		return false;
	}

	m_str = obj["devalias"].asString();
	memset(m_vec[sel].DevAlias, '\0', 36);
	int len = m_str.length() < 36 ? m_str.length() : 36;
	memcpy(m_vec[sel].DevAlias,m_str.c_str(),len);


	m_vec[sel].AliasPos = obj["aliaspos"].asInt();
	m_vec[sel].poeflag = obj["poeflag"].asInt();

	m_str = obj["ip"].asString();
	memset(m_vec[sel].sIPAddr, '\0',  sizeof(m_vec[sel].sIPAddr));
	len = m_str.length() < sizeof(m_vec[sel].sIPAddr) ? m_str.length() : sizeof(m_vec[sel].sIPAddr);
	memcpy(m_vec[sel].sIPAddr, m_str.c_str(), len);

	m_vec[sel].mask[0] = obj["netmask_0"].asUInt();
	m_vec[sel].mask[1] = obj["netmask_1"].asUInt();
	m_vec[sel].mask[2] = obj["netmask_2"].asUInt();
	m_vec[sel].mask[3] = obj["netmask_3"].asUInt();

	m_vec[sel].Port = obj["port"].asInt();
	m_vec[sel].Protocol = obj["protocol"].asInt();

	m_str = obj["username"].asString();
	memset(m_vec[sel].UserName, '\0', MaxNameLen);
	len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
	memcpy(m_vec[sel].UserName, m_str.c_str(), len);

	m_str = obj["password"].asString();
	memset(m_vec[sel].UserPW, '\0', MaxNameLen);
	len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
	memcpy(m_vec[sel].UserPW, m_str.c_str(), len);
	if(!obj["mac"].isNull())
	{
		m_str = obj["mac"].asString();
		memset(m_vec[sel].macAddr, '\0', MaxNameLen);
		len = m_str.length() < MaxNameLen ? m_str.length() : MaxNameLen;
		memcpy(m_vec[sel].macAddr,m_str.c_str(),len);
	}
	if(!obj["ChnNo"].isNull()){
		m_vec[sel].ChnNo = obj["ChnNo"].asInt();
	}
	if(!obj["chnmax"].isNull()){
		m_vec[sel].ChnMax = obj["chnmax"].asInt();
	}

	if(sel < 32)
	{
		m_vec[sel].ChannelMask = 1 << sel;
	}
	else
	{
		m_vec[sel].ChannelMask = 0xFFFF0000 + sel;
	}
	m_vec[sel].StructSize = sizeof(RSNet_SoleIPCSet_t);

	RSNetSetParamParam param;
	memset(&param, '\0',  sizeof(param));
	param.ParamType = MsgParamIpc;
	param.ListParams = &m_vec[sel];
	param.ListParamNum = 1;
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}

int IPCSet::DeleteIpc(Json::Value obj)
{
	int deleteSize = obj.size();
	if(deleteSize == 0)
		return false;
	std::vector<RSNet_SoleIPCSet_t> vecDel;
	for(int i=0; i<deleteSize && i<m_vec.size(); i++)
	{
		int index = obj[i]["deleteindex"].asInt();
		m_vec[index].Enable = 0;
		vecDel.push_back(m_vec[index]);
	}

	if(vecDel.size() == 0)
		return false;

	RSNetSetParamParam param;
	memset(&param, '\0',  sizeof(param));
	param.ParamType = MsgParamIpc;
	param.ListParams = &vecDel[0];
	param.ListParamNum = vecDel.size();
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}

int IPCSet::setRemoteIpcNet( Json::Value obj )
{
	memset(&m_NetIPC,0,sizeof(m_NetIPC));
	m_NetIPC.StructSize = sizeof(m_NetIPC);
	m_NetIPC.ChannelMask = obj["ChannelMask"].asUInt();
	ULONGLONG low = obj["DevTypeULL_Low"].asUInt();
	ULONGLONG high = obj["DevTypeULL_High"].asUInt();
	m_NetIPC.DevTypeULL = (low|(high<<32));
	m_NetIPC.httpPort = obj["httpPort"].asUInt();
	m_NetIPC.mediaPort = obj["mediaPort"].asUInt();
	m_NetIPC.Protocol = obj["Protocol"].asUInt();
	m_NetIPC.Version = obj["Version"].asUInt();
	m_NetIPC.netMode = obj["netMode"].asUInt();
	int len = 0;
	m_str = obj["DevType"].asString();
	memset(m_NetIPC.DevType, '\0', 64);
	len = m_str.length() < 64 ? m_str.length() : 64;
	memcpy(m_NetIPC.DevType,m_str.c_str(),len);

	m_str = obj["Manufacturer"].asString();
	memset(m_NetIPC.Manufacturer, '\0', 64);
	len = m_str.length() < 64 ? m_str.length() : 64;
	memcpy(m_NetIPC.Manufacturer,m_str.c_str(),len);
	
	m_str = obj["DevVersion"].asString();
	memset(m_NetIPC.DevVersion, '\0', 64);
	len = m_str.length() < 64 ? m_str.length() : 64;
	memcpy(m_NetIPC.DevVersion,m_str.c_str(),len);

	m_str = obj["macaddr"].asString();
	memset(m_NetIPC.macaddr, '\0', 64);
	len = m_str.length() < 64 ? m_str.length() : 64;
	memcpy(m_NetIPC.macaddr,m_str.c_str(),len);

	m_str = obj["UserName"].asString();
	memset(m_NetIPC.UserName, '\0', 32);
	len = m_str.length() < 32 ? m_str.length() : 32;
	memcpy(m_NetIPC.UserName,m_str.c_str(),len);

	m_str = obj["Password"].asString();
	memset(m_NetIPC.Password, '\0', 32);
	len = m_str.length() < 32 ? m_str.length() : 32;
	memcpy(m_NetIPC.Password,m_str.c_str(),len);

	for(int i = 0;i < 4;++i)
	{
		m_NetIPC.oldIPAddr[i] = obj["oldIPAddr"][i].asUInt();
		m_NetIPC.ipaddr[i] = obj["ipaddr"][i].asUInt();
		m_NetIPC.submask[i] = obj["submask"][i].asUInt();
		m_NetIPC.gateway[i] = obj["gateway"][i].asUInt();
		m_NetIPC.dns1[i] = obj["dns1"][i].asUInt();
		m_NetIPC.dns2[i] = obj["dns2"][i].asUInt();
	}
	RSNetSetParamParam param;
	memset(&param, '\0',  sizeof(param));
	param.ParamType = MsgIPCNetInfoParam;
	param.ListParams = &m_NetIPC;
	param.ListParamNum = 1;
	int nRet = RSNetSetParam(m_pDevice->GetConnection(), &param);
	if(2 == nRet){
		return 2;//no right
	}else{
		if(nRet){
			return true;
		}else{
			return false;
		}
	}
}
