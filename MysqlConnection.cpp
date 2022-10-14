#include "MysqlConnection.h"


MysqlConnection::MysqlConnection(std::string host, std::string user, std::string passwd, std::string database) {
    if (mysql_init(mysql_) == NULL) {
        printf("mysql init error\n");
    }
    host_ = host;
    user_ = user;
    passwd_ = passwd;
    database_ = database;
    if (!mysql_) {
        // Connect();
    } else {
        printf("mysql is null\n");
    }
}

MysqlConnection::~MysqlConnection() {
    mysql_close(mysql_);   
}


void MysqlConnection::Connect() {
    if (!mysql_real_connect(mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 0, NULL, 0)) {
        printf("mysql connect failed\n");
    } else {
        success_ = true;
    }
}



