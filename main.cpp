#include "source/thread_pool.h"
#include "source/db_connection_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>
#include <string.h>
#include "./thirdparty/rapidjson/document.h"
#include "./thirdparty/rapidjson/writer.h"
#include "./thirdparty/rapidjson/stringbuffer.h"
#include "./thirdparty/workflow/include/WFHttpServer.h"
#include "./source/log.h"
#include "./thirdparty/libhv/include/hv/HttpServer.h"
#include "./thirdparty/libhv/include/hv/hv.h"

using std::cout;
using std::endl;
using namespace hv;
using namespace rapidjson;



int main() {
    MyLog::GetInstance().InitLog();
    // MyLog::GetInstance().GetConsoleObject()->info("hello {}", "world");
    // MyLog::GetInstance().GetFileObject()->info("hello {}", "world");
    // bool ret = Init();
    // if (!ret) {
    //     LOG_ERROR("Init Error!");
    // }

    LOG_ERROR("111 is not %s", "abc");
    return 0;
}
