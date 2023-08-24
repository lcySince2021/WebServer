#ifndef _LOG_H_
#define _LOG_G_

#include "../thirdparty/spdlog/include/spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or “../stdout_sinks.h” if no colors needed
#include "spdlog/sinks/daily_file_sink.h"



class MyLog {
public:
    static MyLog& GetInstance();
protected:
    MyLog();
    ~MyLog();
private:
    MyLog(const MyLog& log) {}
    MyLog& operator = (const MyLog& log) {}
public:
    bool InitLog(int consoleLevel = 0, const int fileLevel = 0, int maxSize = 1000, int backIndex = 10, int isDay = 1);
    auto GetConsoleObject();
    auto GetFileObject();
public:
    int m_isDay;

};


MyLog::MyLog() {
}

MyLog::~MyLog() {
}

MyLog& MyLog::GetInstance() {
    static MyLog instance;
    return instance;
}

auto MyLog::GetConsoleObject() {
    return spdlog::get("console");
}


auto MyLog::GetFileObject() {
    if (m_isDay == 1) {
        return spdlog::get("daily_logger");
    }
    return spdlog::get("file_logger");
}

bool MyLog::InitLog(int consoleLevel, int fileLevel, int maxSize, int backIndex, int isDay) {
    try {
        m_isDay = isDay;
        auto console = spdlog::stdout_logger_mt("console");
        switch (consoleLevel) {
            case 0:
                console->set_level(spdlog::level::trace);
                break;
            case 1:
                console->set_level(spdlog::level::debug);
                break;
            case 2:
                console->set_level(spdlog::level::info);
                break;
            case 3:
                console->set_level(spdlog::level::warn);
                break;
            case 4:
                console->set_level(spdlog::level::err);
                break;
            case 5:
                console->set_level(spdlog::level::critical);
                break;
            case 6:
                console->set_level(spdlog::level::off);
                break;
            defaule:
                console->set_level(spdlog::level::trace);
                break;
        }
        auto file_logger = spdlog::rotating_logger_mt("file_logger", "logs/rotat.log", 1024 * 1024 * maxSize, backIndex);
        auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.log", 0, 0);
        switch (fileLevel) {
            case 0:
                file_logger->set_level(spdlog::level::trace);
                daily_logger->set_level(spdlog::level::trace);
                break;
            case 1:
                file_logger->set_level(spdlog::level::debug);
                daily_logger->set_level(spdlog::level::debug);
                break;
            case 2:
                file_logger->set_level(spdlog::level::info);
                daily_logger->set_level(spdlog::level::info);
                break;
            case 3:
                file_logger->set_level(spdlog::level::warn);
                daily_logger->set_level(spdlog::level::warn);
                break;
            case 4:
                file_logger->set_level(spdlog::level::err);
                daily_logger->set_level(spdlog::level::err);
                break;
            case 5:
                file_logger->set_level(spdlog::level::critical);
                daily_logger->set_level(spdlog::level::critical);
                break;
            case 6:
                file_logger->set_level(spdlog::level::off);
                daily_logger->set_level(spdlog::level::off);
                break;
            default:
                file_logger->set_level(spdlog::level::trace);
                daily_logger->set_level(spdlog::level::trace);
                break;
        }
    }
    catch (const spdlog::spdlog_ex& ex) {
        return false;
        std::cout << "Log Init failed:" << ex.what() << std::endl;
    }
    return true;
}

#define LOG_INFO(fmt, ...)  do {    \
                                {   \
                                    char buffer[256];   \
                                    sprintf(buffer, fmt, __VA_ARGS__);  \
                                    std::string message(buffer);    \
                                    MyLog::GetInstance().GetFileObject()->info(message); \
                                }   \
                            } while(0)
#define LOG_DEBUG(fmt, ...)  do {    \
                                {   \
                                    char buffer[256];   \
                                    sprintf(buffer, fmt, __VA_ARGS__);  \
                                    std::string message(buffer);    \
                                    MyLog::GetInstance().GetFileObject()->debug(message); \
                                }   \
                            } while(0)
#define LOG_ERROR(fmt, ...)  do {    \
                                {   \
                                    char buffer[256];   \
                                    sprintf(buffer, fmt, __VA_ARGS__);  \
                                    std::string message(buffer);    \
                                    MyLog::GetInstance().GetFileObject()->error(message); \
                                }   \
                            } while(0)

#endif // _LOG_H_
