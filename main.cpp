#include "MysqlConnection.h"


int main() {
    MysqlConnection conn("127.0.0.1", "root", "123456", "test");
    conn.Connect();
    if (!conn.IsValid()) {
        printf("failed\n");
    }
    return 0;
    
}
