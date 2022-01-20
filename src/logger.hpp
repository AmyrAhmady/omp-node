#pragma once
#include <sstream>

#define L_INFO ompnode::Log().Get(ompnode::LogLevel::LOG_INFO)
#define L_DEBUG ompnode::Log().Get(ompnode::LogLevel::LOG_DEBUG)
#define L_WARN ompnode::Log().Get(ompnode::LogLevel::LOG_WARN)
#define L_ERROR ompnode::Log().Get(ompnode::LogLevel::LOG_ERROR)

namespace ompnode {

	enum class LogLevel {
		LOG_ERROR = 0, // level 1
		LOG_WARN = 1, // level 2
		LOG_DEBUG = 2, // level 3
		LOG_INFO = 3, // level 4
		LOG_FULL = 4
	};

	class Log {
	public:
		static LogLevel logLevel;

		static void Init(LogLevel level = logLevel);

		Log();

		virtual ~Log();

		std::ostringstream &Get(LogLevel level = LogLevel::LOG_INFO);

	protected:
		std::ostringstream os;
	private:
		LogLevel currentLevel;

		std::string GetLevelName(LogLevel messageLevel);

		Log(const Log &);
	};

}