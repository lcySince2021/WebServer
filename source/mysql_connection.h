#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_
#include "mysql/mysql.h"
#include <string>
#include <iostream>

class MysqlConnection {
public:

    MysqlConnection();
    ~MysqlConnection();
public:
    std::string host_ = "";
    int port_;
    std::string user_ = "";
    std::string passwd_ = "";
    std::string database_ = "";
public:
    bool Init();
    bool Init(std::string host, int port, std::string user, std::string passwd, std::string database);
    bool ReConnect();

    // insert delete update drop
    bool Update(const std::string& sql);

    // query
    bool Query(const std::string& sql);

    bool IsValid() { return is_inited_; }
    MYSQL* GetConn() { return &mysql_; }
private:
    MYSQL mysql_;
    MYSQL_ROW row_;
    MYSQL_FIELD* field_;
    MYSQL_RES* result_;
    bool is_inited_ = false;
};


#endif
