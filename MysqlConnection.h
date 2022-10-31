#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_
#include "mysql/mysql.h"
#include <string>

class MysqlConnection {
public:
    MysqlConnection(std::string host, std::string user, std::string passwd, std::string database);
    ~MysqlConnection();
    bool IsValid() { return m_success; };
public:
    std::string m_host;
    std::string m_user;
    std::string m_passwd;
    std::string m_database;
public:
    void Connect();
private:
    MYSQL *m_mysql = nullptr;
    MYSQL_ROW *m_row = nullptr;
    MYSQL_FIELD *m_field = nullptr;
    MYSQL_RES *m_result = nullptr;
    bool m_success = false;
};


#endif
