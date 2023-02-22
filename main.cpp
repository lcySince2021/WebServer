#include "source/thread_pool.h"
#include "source/db_connection_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>
#include "./thirdparty/libhv/include/hv/HttpServer.h"
#include "./thirdparty/rapidjson/document.h"
#include "./thirdparty/rapidjson/writer.h"
#include "./thirdparty/rapidjson/stringbuffer.h"

using std::cout;
using std::endl;
using namespace hv;
using namespace rapidjson;

void JsonTest() {
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);
 
    // 2. 利用 DOM 作出修改。
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
 
    // 3. 把 DOM 转换（stringify）成 JSON。
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
 
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
}

int main() {
    JsonTest();
    /*auto db_pool = MysqlConnPool::GetInstance();
    db_pool->Init("127.0.0.1", 3306, "root", "123456", "lcy", 8);
    int count = db_pool->GetFree();
    cout << count << endl;
    auto conn = db_pool->GetFree();
    ThreadPool pool(4);
    std::vector<std::future<void>> results;
    int num = 15;
    while (num--) {
        results.emplace_back(pool.enqueue([]() { 
                printf("thread id: %llu\n", std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }));
    }
    for (auto& result : results) {
        // result.get();
    }*/

    // start server
    // hv::HttpService router;
    // router.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
    //         return resp->String("pong");
    //         });
    // HttpServer server;
    // server.registerHttpService(&router);
    // server.setPort(8080);
    // server.setThreadNum(4);
    // server.run();
    return 0;
    
}
