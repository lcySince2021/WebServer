#ifndef _DB_CONNECTION_POOL_H_
#define _DB_CONNECTION_POOL_H_
#include <queue>
#include <stdio.h>
#include <thread>
#include "mysql_connection.h"


class DbConnectionPool {
public:
    static DbConnectionPool* GetInstance() {
        static DbConnectionPool instance;
        return &instance;
    }
    ~DbConnectionPool() {
        while (!connection_list_.empty()) {
            auto conn = connection_list_.front();
            connection_list_.pop();
            conn->~MysqlConnection();
        }
    }

    void SetPararmeter(int max_connect_count, const std::string& host, int port, const std::string& username, const std::string& password, const std::string database) {
        printf("set config\n");
        max_connect_count_ = max_connect_count;
        connect_count_ = 0;
        host_ = host;
        port_ = port;
        username_ = username;
        password_ = password;
        database_ = database;
    }

    bool Init() {
        for (int i = 0; i < max_connect_count_; ++i) {
            MysqlConnection* connect = new MysqlConnection();
            if (!connect->Init(host_, port_, username_, password_, database_)) {
                return false;
            }
            connection_list_.push(connect);
        }
        return true;
    }
    

    int GetMaxConnectCount() { return connection_list_.size(); }
    int GetFreeCount() { return connection_list_.size() - connect_count_; }

    bool Update(const std::string& sql) {
        int count = 0;
        while (connection_list_.empty() && count < retry_num_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        if (count < retry_num_) {
            auto conn = connection_list_.front();
            connection_list_.pop();
            if (!conn->Update(sql)) {
                // 更新失败,重新加入池中
                connection_list_.push(conn);
                return false;
            }
            // 更新成功，重新加入池中
            printf("--------------------------");
            connection_list_.push(conn);
            return true;
            // if (!mysql_ping(conn->GetConn())) {
            //     if (!conn->ReConnect()) {
            //         connection_list_.push(conn);
            //         return false;
            //     }
            //     if (!conn->Update(sql)) {
            //         // 更新失败,重新加入池中
            //         connection_list_.push(conn);
            //         return false;
            //     }
            //     // 更新成功，重新加入池中
            //     connection_list_.push(conn);
            //     return true;
            // } 
        }
        // 超时
        return false;
    }
    


private:
    DbConnectionPool() {
        printf("create DbConnectionPool\n");
    }
    

private:
    int retry_num_ = 100;
    int max_connect_count_;
    int connect_count_;
    std::string host_;
    int port_;
    std::string username_;
    std::string password_;
    std::string database_;
    // MysqlConnection mysql_connection_;
    std::queue<MysqlConnection*> connection_list_;
};

#endif
