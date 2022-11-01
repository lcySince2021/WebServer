#include "source/mysql_connection.h"
#include <iostream>



int main() {
    auto& con = MysqlConnection::GetInstance();
    if (con.Init("127.0.0.1", 3306, "root", "123456", "lcy")) {
        printf("mysql connect success!\n");    
    }

    return 0;
    
}
