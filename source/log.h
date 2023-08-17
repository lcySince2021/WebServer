#ifndef _LOG_H_
#define _LOG_H_
#include "../thirdparty/spdlog/include/spdlog/spdlog.h"
#include "../thirdparty/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "../thirdparty/spdlog/include/spdlog/sinks/daily_file_sink.h"


// 记录不同日志等级的宏
#define LOG_TRACE(format, ...) spdlog::trace(format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) spdlog::debug(format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) spdlog::info(format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) spdlog::warn(format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) spdlog::error(format, ##__VA_ARGS__)

class MyLog {
public:
    enum OutPosition {
        CONSOLE             = 0x01,
        FILE                = 0x02,
        CONSOLE_AND_FILE    = 0x03,
    };


    enum OutMode {
        SUNC,
        ASUNC, // 异步
    };
};

    

#endif
