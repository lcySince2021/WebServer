#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_
#include "mysql/mysql.h"
#include <string>
#include <iostream>

class MysqlConnection {
public:
    static MysqlConnection& GetInstance() {
        static MysqlConnection connection;
        return connection;
    }
    ~MysqlConnection();
public:
    std::string host_ = "";
    int port_;
    std::string user_ = "";
    std::string passwd_ = "";
    std::string database_ = "";
public:
    MysqlConnection();
    bool Init();
    bool Init(std::string host, int port, std::string user, std::string passwd, std::string database);
    bool ReConnect();
private:
    MYSQL mysql_;
    MYSQL_ROW row_;
    MYSQL_FIELD field_;
    MYSQL_RES result_;
};


#endif
