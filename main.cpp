#include "source/mysql_connection.h"
//#include "source/http.h"
#include "source/thread_pool.h"
#include <iostream>

using namespace std;

int main() {
    auto& con = MysqlConnection::GetInstance();
    if (con.Init("127.0.0.1", 3306, "root", "123456", "lcy")) {
        printf("mysql connect success!\n");    
    }
    //string sql = "insert into test (id, name) values (1, 'test')";
    //string sql2 = "delete from lcy where id = 1";
    //string sql3 = "update test set name = 'lcy' where id = 1";
    //con.Update(sql2);
    // con.Update(sql3);
    // string sql = "select * from test";
    // con.Query(sql);
    string sql = "drop table test";
    con.Update(sql);
    return 0;
    
}
