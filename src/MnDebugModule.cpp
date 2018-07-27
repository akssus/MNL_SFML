#include "MnDebugModule.h"
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
using namespace MNL;

void MnDebugModule::WriteLog(const std::string & log, MnDebugLogLevel logLevel)
{
	m_lstLogs.push_back(_LogPrefix(logLevel) + log);
}

void MnDebugModule::Update()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration<double>(currentTime - m_baseTime);
	auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime);
	
	if (elapsedSeconds.count() > FLUSH_PERIOD_SEC)
	{
		const auto filePath = LOGFILE_ROOT + _LogFileNameByTime();
		_FlushLogsToFile(filePath);
	}
}

void MnDebugModule::_ResetTimer()
{
	m_baseTime = std::chrono::system_clock::now();
}

std::string MnDebugModule::_LogPrefix(MnDebugLogLevel logLevel)
{
	switch(logLevel)
	{
	case MN_LOGTYPE_LOG: return "LOG: ";
	case MN_LOGTYPE_WARNING: return "WARNING: ";
	case MN_LOGTYPE_ERROR: return "ERROR: ";
	default: return "LOG: "; //디폴트가 될 이유가 없지만
	}
}

std::string MnDebugModule::_LogFileNameByTime()
{
	auto nowTime_raw = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	auto nowTime = std::localtime(&nowTime_raw);
	std::string year = std::to_string(nowTime->tm_year);
	std::string month = std::to_string(nowTime->tm_mon + 1);
	std::string day = std::to_string(nowTime->tm_mday);
	std::string hour = std::to_string(nowTime->tm_hour);
	std::string minute = std::to_string(nowTime->tm_min);
	std::string second = std::to_string(nowTime->tm_sec);

	return year + month + day + hour + minute + second;
}

void MnDebugModule::_FlushLogsToFile(const std::string& filePath)
{
	//파일스트림 생성
	std::ofstream fstream;
	try
	{
		fstream.open(filePath);
		if (!fstream.is_open()) { return; }

		for (auto& log : m_lstLogs)
		{
			fstream << log << std::endl;
		}
		fstream.close();
	}
	catch(std::exception e)
	{
		WriteLog(e.what(), MN_LOGTYPE_ERROR);
		if (fstream.is_open())
		{
			fstream.close();
		}
	}

	m_lstLogs.clear();
}


//-----------------------------------------------------------------------------------------------------------
//MnDebug
//-----------------------------------------------------------------------------------------------------------

bool MnDebug::m_isInitialized = false;

void MnDebug::SetDebugModule(const std::shared_ptr<MnDebugModule>& spDebugModule)
{
	if (spDebugModule == nullptr) { return; }

	m_spDebugModule = spDebugModule;
	m_isInitialized = true;
}

void MnDebug::WriteLog(const std::string& log, MnDebugLogLevel logLevel)
{
	if (!m_isInitialized) { return; }

	m_spDebugModule->WriteLog(log, logLevel);
}
