#include "mysql_connection.h"


MysqlConnection::MysqlConnection() {
    printf("create\n");
}

MysqlConnection::~MysqlConnection() {
    mysql_close(&mysql_);   
    printf("delete\n");
}


bool MysqlConnection::Init() {
    if (!mysql_init(&mysql_)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql init failed\n");
        return false;
    }
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    } else {
        return true;
    }
}

bool MysqlConnection::Init(std::string host, int port, std::string user, std::string passwd, std::string database) {
    host_ = host;
    port_ = port;
    user_ = user;
    passwd_ = passwd;
    database_ = database;
    if (!mysql_init(&mysql_)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql init failed\n");
        return false;
    }
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    } else {
        return true;
    }
}

bool MysqlConnection::ReConnect() {
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    } else {
        return true;
    }
}



