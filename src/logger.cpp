#include <fstream>
#include <iostream>
#include <ctime>
#include "logger.hpp"

LogLevel Log::logLevel = LogLevel::Debug;

void Log::Init(LogLevel level) {
	logLevel = level;
	char chLogBuff[128];
	char timestamp_buff[30];
	struct tm* current_tm;
	time_t current_time = time(NULL);

	current_tm = localtime(&current_time);
	sprintf(timestamp_buff,
		"[%02d/%02d/%d - %02d:%02d:%02d] %%s\n",
		current_tm->tm_mday,
		current_tm->tm_mon + 1,
		current_tm->tm_year + 1900,
		current_tm->tm_hour,
		current_tm->tm_min,
		current_tm->tm_sec);
	sprintf(chLogBuff, timestamp_buff, "-> [PLUGIN] omp-node plugin started...");

	std::ofstream file("omp-node.log", std::ofstream::out | std::ofstream::app);
	if (file.is_open()) {
		file << chLogBuff;
		file.close();
	}
}

std::ostringstream& Log::Get(LogLevel level) {
	currentLevel = level;
	if (logLevel <= level) {
		time_t curr_time;
		curr_time = time(NULL);
		struct tm* tm_local;
		tm_local = localtime(&curr_time);

		char month_buff[12];
		char time_buff[12];
		sprintf(month_buff, "%02d/%02d/%d", tm_local->tm_mday, tm_local->tm_mon + 1, tm_local->tm_year + 1900);
		sprintf(time_buff, "%02d:%02d:%02d", tm_local->tm_hour, tm_local->tm_min, tm_local->tm_sec);
		os << "[" << month_buff << " - " << time_buff << "]";
		os << " -> " << GetLevelName(level) << ": ";
		return os;
	}
	else {
		os.str("");
		return os;
	}
}

Log::Log() {

}

Log::~Log() {
	if (logLevel <= currentLevel) {
		os << std::endl;

		std::ofstream file("omp-node.log", std::ofstream::out | std::ofstream::app);
		if (file.is_open()) {
			file << os.str();
			std::cout << os.str();
			os.str("");
			os.clear();
		}
	}
}

Impl::String Log::GetLevelName(LogLevel level) {
	Impl::String levelName = "[LOG_UNKNOWN]";
	switch (level) {
	case LogLevel::Error: levelName = "[ERROR]";
		break;
	case LogLevel::Warning: levelName = "[WARNING]";
		break;
	case LogLevel::Message: levelName = "[MESSAGE]";
		break;
	case LogLevel::Debug: levelName = "[DEBUG]";
		break;
	}
	return levelName;
}