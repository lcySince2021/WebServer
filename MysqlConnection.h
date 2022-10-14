#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_
#include "mysql/mysql.h"
#include <string>

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
    MYSQL *mysql_ = nullptr;
    MYSQL_ROW *row_ = nullptr;
    MYSQL_FIELD *field = nullptr;
    MYSQL_RES *result = nullptr;
    bool success_ = false;
};


#endif
