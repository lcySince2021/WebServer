#include "MysqlConnection.h"


MysqlConnection::MysqlConnection(std::string host, std::string user, std::string passwd, std::string database) {
    if (mysql_init(&mysql_) == NULL) {
        printf("mysql init error\n");
    }
    host_ = host;
    user_ = user;
    passwd_ = passwd;
    database_ = database;
}

MysqlConnection::~MysqlConnection() {
    mysql_close(&mysql_);   
}


void MysqlConnection::Connect() {
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
    } else {
        success_ = true;
    }
}



