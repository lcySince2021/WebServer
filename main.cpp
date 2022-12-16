#include "source/thread_pool.h"
#include "source/db_connection_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>

using std::cout;
using std::endl;

int main() {
    auto db_pool = MysqlConnPool::GetInstance();
    db_pool->Init("127.0.0.1", 3306, "root", "123456", "lcy", 8);
    int count = db_pool->GetFree();
    cout << count << endl;
    auto conn = db_pool->GetFree();
    ThreadPool pool(4);
    std::vector<std::future<int>> results;
    int num = 15;
    while (num--) {
        results.emplace_back(pool.enqueue([](int num) { 
                printf("thread id: %llu\n", std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                return num; 
                }, 4));
    }
    for (auto& result : results) {
        result.get();
    }
    return 0;
    
}
