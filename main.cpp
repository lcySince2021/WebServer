#include "source/mysql_connection.h"
//#include "source/http.h"
#include "source/thread_pool.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>


using namespace std;

pthread_t id1, id2;
pthread_rwlock_t rwlock;

void *fun1(void* data) {
    auto& con = MysqlConnection::GetInstance();
    int n = 1000;
    while (n--) {
        string sql1 = "insert into test (id, name) values (1, 'test')";
        string sql2 = "delete from test where id = 1";
        con.Update(sql1);
        con.Update(sql2);
    }
    return ((void*)0);
}

void *fun2(void* data) {
    auto& con = MysqlConnection::GetInstance();
    int n = 1000;
    while (n--) {
        string sql1 = "insert into test (id, name) values (2, 'test')";
        string sql2 = "delete from test where id = 2";
        con.Update(sql1);
        con.Update(sql2);
    }
    return ((void*)0);
}


int main() {
    auto& con = MysqlConnection::GetInstance();
    if (con.Init("127.0.0.1", 3306, "root", "123456", "lcy")) {
        printf("mysql connect success!\n");    
    }
    
    pthread_create(&id1, NULL, fun1, NULL);
    pthread_create(&id1, NULL, fun2, NULL);
    
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    sleep(600000);
    return 0;
    
}
