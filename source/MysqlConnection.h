#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_
#include "mysql/mysql.h"
#include <string>
#include <iostream>

class MysqlConnection {
public:
    MysqlConnection(std::string host, std::string user, std::string passwd, std::string database);
    ~MysqlConnection();
    bool IsValid() { return success_; };
public:
    std::string host_;
    std::string user_;
    std::string passwd_;
    std::string database_;
public:
    void Connect();
private:
    MYSQL mysql_;
    MYSQL_ROW row_;
    MYSQL_FIELD field_;
    MYSQL_RES result_;
    bool success_ = false;
};


#endif
