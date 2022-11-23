#include "source/thread_pool.h"
#include "source/db_connection_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>

using namespace std;


int main() {
    auto db_pool = DbConnectionPool::GetInstance();
    db_pool->SetPararmeter(8, "127.0.0.1", 3306, "root", "123456", "lcy");
    db_pool->Init();
    printf("max connect count: %d\n", db_pool->GetMaxConnectCount());
    std::string sql = "insert into 'test' values(5, 'test');";
    
    std::string sql1 = "delete from test where id = 5;";
    bool ret = db_pool->Update(sql);
    ret = db_pool->Update(sql1);
    // ThreadPool pool(4);
    // std::vector<std::future<int>> results;
    // int num = 15;
    // while (num--) {
    //     results.emplace_back(pool.enqueue([](int num) { 
    //             printf("thread id: %llu\n", std::this_thread::get_id());
    //             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //             return num; 
    //             }, 4));
    // }
    // for (auto& result : results) {
    //     // std::cout << result.get() << std::endl;
    //     result.get();
    // }
    return 0;
    
}
