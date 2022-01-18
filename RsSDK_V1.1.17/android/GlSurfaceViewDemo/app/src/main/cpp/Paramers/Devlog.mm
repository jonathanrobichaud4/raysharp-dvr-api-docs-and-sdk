#include "StdAfx.h"
#include "Devlog.h"

Devlog::Devlog(void)
{
	memset(&m_Req,0,sizeof(LogSearchInput_t));
	m_TotalNum = 0;
	m_StructSize = 0;
	m_pData = NULL;
}

Devlog::~Devlog(void)
{
	if(m_pData != NULL){
		delete [] m_pData;
		m_pData = NULL;
	}
}

int Devlog::SearchLogProc(void* data,unsigned int size)
{
	unsigned char* pData = (unsigned char*)data;
	unsigned char* pEndData = pData + size;

	m_TotalNum = *(int*)pData;

	pData += sizeof(int);
	m_StructSize = *(unsigned int*)pData;

	pData += sizeof(unsigned int);

	if(m_pData != NULL){
		delete [] m_pData;
		m_pData = NULL ;
	}

	m_pData = new unsigned char[m_TotalNum*m_StructSize];
	memcpy(m_pData,pData,m_TotalNum * m_StructSize );

	return true ;
}

void RSNET_CALL Devlog::RSSearchLogCallback(void* data, unsigned int size, void* userParam)
{
	Devlog* pThis = (Devlog*)userParam;
	if(pThis != NULL && data != NULL && size > 0 )
	{
		pThis->SearchLogProc(data,size);
	}
}

std::string Devlog::QueryAll(std::string strData)
{
	//请求数据
	std::string strRst = "err";

	Json::Reader reader;
	Json::Value obj;
	if(!reader.parse(strData, obj)){
		return strRst;
	}

	RSNetQueryLogParam param;
	memset(&param, '\0', sizeof(param));

	memset(&m_Req,'\0', sizeof(LogSearchInput_t));
	m_Req.Start.time.year = obj["year1"].asUInt();
	m_Req.Start.time.month = obj["month1"].asUInt();
	m_Req.Start.time.day = obj["day1"].asUInt();
	m_Req.Start.time.hour = obj["hour1"].asUInt();
	m_Req.Start.time.minute = obj["minute1"].asUInt();
	m_Req.Start.time.second = obj["second1"].asUInt();

	m_Req.End.time.year = obj["year2"].asUInt();
	m_Req.End.time.month = obj["month2"].asUInt();
	m_Req.End.time.day = obj["day2"].asUInt();
	m_Req.End.time.hour = obj["hour2"].asUInt();
	m_Req.End.time.minute = obj["minute2"].asUInt();
	m_Req.End.time.second = obj["second2"].asUInt();

	int iMainType = obj["MainType"].asInt();
	m_Req.MainType = (LogMainType_E)iMainType ;
	m_Req.SubType = obj["SubType"].asInt();

	param.param = &m_Req;
	param.DataCallback = RSSearchLogCallback;
	param.UserParam = this;

	m_TotalNum = 0 ;
	m_StructSize = 0 ;
	if(m_pData != NULL){
		delete [] m_pData;
		m_pData = NULL ;
	}

	if(RSNetQueryLog(m_pDevice->GetConnection(),&param))
	{
		if(m_pData == NULL){
			return "suc";
		}

		unsigned char* pDataPos = m_pData;//数据头

		IpcLog_t LogData;
		memset(&LogData,0,sizeof(IpcLog_t));

		
		Json::Value data(Json::objectValue);
		Json::Value logData(Json::objectValue);

		m_obj.clear();
		for(int i=0; i< m_TotalNum; ++i)
		{
			data.clear();
			logData.clear();

			memset(&LogData,0,sizeof(IpcLog_t));
			pDataPos = m_pData + i * m_StructSize;
			memcpy(&LogData,pDataPos,m_StructSize);//一次获取一个通道数据，保存在 LogData 里

			char bufTime[256] = {0};
			sprintf(bufTime, "%04d-%02d-%02d %02d:%02d:%02d", 
			LogData.time.time.year,
			LogData.time.time.month,
			LogData.time.time.day,
			LogData.time.time.hour,
			LogData.time.time.minute,
			LogData.time.time.second);
			data["time"] = bufTime;

			data["Operation"] = LogData.Operation;
			data["MainType"] = LogData.MainType;
			data["Level"] = LogData.Level;

			iMainType = LogData.MainType;
			
			switch(iMainType)
			{
			case LOG_SYSTEM:
				{
					logData["UserName"] = LogData.LogInfo.SystemLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.SystemLog.IPaddr;

						char bufSrc[256] = {0};
						sprintf(bufSrc, "%04d-%02d-%02d %02d:%02d:%02d",
							LogData.LogInfo.SystemLog.TimeSrc.year,
							LogData.LogInfo.SystemLog.TimeSrc.month,
							LogData.LogInfo.SystemLog.TimeSrc.day,
							LogData.LogInfo.SystemLog.TimeSrc.hour,
							LogData.LogInfo.SystemLog.TimeSrc.minute,
							LogData.LogInfo.SystemLog.TimeSrc.second);
					logData["TimeSrc"] = bufSrc;

						char bufDst[256] = {0};
						sprintf(bufDst, "%04d-%02d-%02d %02d:%02d:%02d",
							LogData.LogInfo.SystemLog.TimeDst.year,
							LogData.LogInfo.SystemLog.TimeDst.month,
							LogData.LogInfo.SystemLog.TimeDst.day,
							LogData.LogInfo.SystemLog.TimeDst.hour,
							LogData.LogInfo.SystemLog.TimeDst.minute,
							LogData.LogInfo.SystemLog.TimeDst.second);
					logData["TimeDst"] = bufDst;
				}
				break;
			case LOG_NETWORK:
				{
					logData["UserName"] = LogData.LogInfo.NetworkLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.NetworkLog.IPaddr;
					logData["Record"] = LogData.LogInfo.NetworkLog.Record;
				}
				break;
			case LOG_CONFIG:
				{
					logData["UserName"] = LogData.LogInfo.ConfigLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.ConfigLog.IPaddr;
				}
				break;
			case LOG_ALARM:
				{
					logData["Record"] = LogData.LogInfo.AlarmLog.Record;
					logData["ChnID"] = LogData.LogInfo.AlarmLog.ChnID;
				}
				break;
			case LOG_USER:
				{
					logData["UserName"] = LogData.LogInfo.UserLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.UserLog.IPaddr;
					logData["DstUser"] = LogData.LogInfo.UserLog.DstUser;
				}
				break;
			case LOG_RECORD:
				{
					logData["UserName"] = LogData.LogInfo.RecordLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.RecordLog.IPaddr;
					logData["EndTime"] = LogData.LogInfo.RecordLog.EndTime;

						char buf[256] = {0};
						sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
							LogData.LogInfo.RecordLog.StartTime.year,
							LogData.LogInfo.RecordLog.StartTime.month,
							LogData.LogInfo.RecordLog.StartTime.day,
							LogData.LogInfo.RecordLog.StartTime.hour,
							LogData.LogInfo.RecordLog.StartTime.minute,
							LogData.LogInfo.RecordLog.StartTime.second);
					logData["StartTime"] = buf;
				}
				break;
			case LOG_STORAGE:
				{
					logData["UserName"] = LogData.LogInfo.StorageLog.UserName;
					logData["IPaddr"] = LogData.LogInfo.StorageLog.IPaddr;
					logData["SeriorNo"] = LogData.LogInfo.StorageLog.SeriorNo;
					logData["Result"] = LogData.LogInfo.StorageLog.Result;
					logData["HddID"] = LogData.LogInfo.StorageLog.HddID;
				}
				break;
			default:break;
			}
			data["LogInfo"] = logData;
			m_obj["logArr"].append(data);
		}

		Json::FastWriter writer;
		strRst = writer.write(m_obj);
	}

	return strRst;
}
