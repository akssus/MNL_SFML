#pragma once
#include "MnGameSystemModule.h"
#include <chrono>
#include <list>

namespace MNL
{
	enum MnDebugLogLevel
	{
		MN_LOGTYPE_LOG,
		MN_LOGTYPE_WARNING,
		MN_LOGTYPE_ERROR,
	};

	class MnDebugModule : public MnGameSystemModule
	{
	public:
		void WriteLog(const std::string& log, MnDebugLogLevel logLevel);
		//일정 주기로 Flush한다
		void Update() override;

	private:
		void _ResetTimer();
		std::string _LogPrefix(MnDebugLogLevel logLevel);
		std::string _LogFileNameByTime();
		void _FlushLogsToFile(const std::string& filePath);

	private:
		const std::string LOGFILE_ROOT = "Log/";
		const uint32_t FLUSH_PERIOD_SEC = 600u;
		std::chrono::system_clock::time_point m_baseTime;

		std::list<std::string> m_lstLogs;
	};


	//전역 접근용 스테틱 클래스
	class MnDebug
	{
	public:
		static void SetDebugModule(const std::shared_ptr<MnDebugModule>& spDebugModule);
		static void WriteLog(const std::string& log, MnDebugLogLevel logLevel);

	private:
		static bool m_isInitialized;
		static std::shared_ptr<MnDebugModule> m_spDebugModule;
	};

}
