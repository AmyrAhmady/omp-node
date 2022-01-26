#pragma once
#include <sstream>
#include "core.hpp"

#define L_ERROR Log().Get(LogLevel::Error)
#define L_WARN Log().Get(LogLevel::Warning)
#define L_MESSAGE Log().Get(LogLevel::Message)
#define L_DEBUG Log().Get(LogLevel::Debug)

class Log {
public:
    static LogLevel logLevel;

    static void Init(LogLevel level = logLevel);

    Log();

    virtual ~Log();

    std::ostringstream &Get(LogLevel level = LogLevel::Message);

protected:
    std::ostringstream os;
private:
    LogLevel currentLevel;

    std::string GetLevelName(LogLevel messageLevel);

    Log(const Log &);
};