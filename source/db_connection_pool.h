#ifndef _DB_CONNECTION_POOL_H_
#define _DB_CONNECTION_POOL_H_
#include <list>
#include "mysql_connection.h"


class DbConnectionPool {
public:
    DbConnectionPool(int count);
    ~DbConnectionPool();
    void SetPararmeter(int max_connect_num, const std::string& host, int port,
                        const std::string& username, const std::string& password,
                        const std::string database);


private:
    int max_connect_num_;
    int connect_num_;
    std::string host_;
    int port_;
    std::string username_;
    std::string password_;
    std::string database_;
    MysqlConnection mysql_connection_;
    std::list<MYSQL*> connection_lists_;
};

#endif
