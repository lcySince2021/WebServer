#include "source/mysql_connection.h"
//#include "source/http.h"
#include "source/thread_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>

using namespace std;


int main() {
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
        // std::cout << result.get() << std::endl;
        result.get();
    }
    return 0;
    
}
