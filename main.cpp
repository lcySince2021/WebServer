#include "source/mysql_connection.h"
//#include "source/http.h"
#include "source/thread_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>


using namespace std;


int main() {
    ThreadPool pool(4);
    auto result = pool.enqueue([](int num) { 
            printf("thread id: %llu\n", std::this_thread::get_id());
            return num; 
            }, 4);
    std::cout << result.get() << std::endl;
    return 0;
    
}
