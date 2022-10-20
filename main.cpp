#include "source/MysqlConnection.h"


int main() {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_real_connect(&mysql, "host", "root",  "123456", "lcy", 0, NULL, 0);
    // MysqlConnection conn("host", "root", "123456", "lcy");
    // conn.Connect();
    // if (!conn.IsValid()) {
    //     printf("failed\n");
    // }
    

    return 0;
    
}
