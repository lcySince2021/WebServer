#ifndef _DB_CONNECTION_POOL_H_
#define _DB_CONNECTION_POOL_H_
#include <list>
#include "mysql_connection.h"


class DbConnectionPool {
public:
    static DbConnectionPool& GetInstance() {
        static DbConnectionPool instance;
        return instance;
    }
    ~DbConnectionPool() {}
    void SetPararmeter(int max_connect_num, const std::string& host, int port, const std::string& username, const std::string& password, const std::string database) {
        max_connect_num_ = max_connect_num_;
        host_ = host;
        port_ = port;
        username_ = username;
        password_ = password;
    }
    int GetMaxConnectCount() { return max_connect_num_; }
    int GetConnectCount() { return connect_num_; }


private:
    DbConnectionPool() {
        for (int i = 0; i < max_connect_num_; ++i) {
            MYSQL* mysql;
            if (!mysql_init(mysql)) {
                return;
            }
            if (!mysql_real_connect(mysql, host_.c_str(), username_.c_str(), password_.c_str(), database_.c_str(), port_, NULL, 0)) {
                return;
            }
            connection_lists_.push_back(mysql);
        }
    }
    

private:
    int max_connect_num_;
    int connect_num_;
    std::string host_;
    int port_;
    std::string username_;
    std::string password_;
    std::string database_;
    // MysqlConnection mysql_connection_;
    std::list<MYSQL*> connection_lists_;
};

#endif
