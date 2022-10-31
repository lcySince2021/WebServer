#include "source/MysqlConnection.h"
#include "source/DbConnection.h"
#include <iostream>

int main() {
    auto& con = DbConnection::get_instance();
    auto& con2 = DbConnection::get_instance();
    MysqlConnection conn("127.0.0.1", "root", "123456", "lcy");
    conn.Connect();
    if (!conn.IsValid()) {
        printf("failed\n");
    } else {
        printf("Connect success!\n");
    }
    

    return 0;
    
}
