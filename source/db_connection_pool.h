#ifndef _DB_CONNECTION_POOL_H_
#define _DB_CONNECTION_POOL_H_
#include <list>
#include "mysql_connection.h"


class DbConnectionPool {
public:
    static DbConnectionPool* GetInstance() {
        static DbConnectionPool instance;
        return &instance;
    }
    ~DbConnectionPool() {}
    void SetPararmeter(int max_connect_count, const std::string& host, int port, const std::string& username, const std::string& password, const std::string database) {
        printf("set config\n");
        max_connect_count_ = max_connect_count;
        connect_count_ = 0;
        host_ = host;
        port_ = port;
        username_ = username;
        password_ = password;
    }

    bool Init() {
        for (int i = 0; i < max_connect_count_; ++i) {
            MYSQL* mysql;
            if (!mysql_init(mysql)) {
                printf("mysql_init failed, num:%d\n", i);
                return false;
            }
            if (!mysql_real_connect(mysql, host_.c_str(), username_.c_str(), password_.c_str(), database_.c_str(), port_, NULL, 0)) {
                printf("mysql_real_connect failed, num:%d\n", i);
                return false;
            }
            connection_lists_.push_back(mysql);
        }
        return true;
    }
    

    int GetMaxConnectCount() { return connection_lists_.size(); }
    int GetConnectCount() { return connect_count_; }
    


private:
    DbConnectionPool() {
        printf("create DbConnectionPool\n");
        
    }
    

private:
    int max_connect_count_;
    int connect_count_;
    std::string host_;
    int port_;
    std::string username_;
    std::string password_;
    std::string database_;
    // MysqlConnection mysql_connection_;
    std::list<MYSQL*> connection_lists_;
};

#endif
