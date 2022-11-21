#include "db_connection_pool.h" 


DbConnectionPool::DbConnectionPool(int count) {
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
void DbConnectionPool::SetPararmeter(int max_connect_num, const std::string& host, int port, 
        const std::string& username, const std::string& password, 
        const std::string& database) {
    max_connect_num_ = max_connect_num_;

    host_ = host;
    port_ = prot;
    username_ = username;
    password_ = password;
}
