#include "db_connection_pool.h"

MysqlConnPool* MysqlConnPool::GetInstance() {
   static MysqlConnPool instance;
   return &instance;
}

void MysqlConnPool::Init(const std::string& host, int port, const std::string& user, const std::string& passwd, const std::string& database, int max_conn_count) {
    host_ = host;
    port_ = port;
    user_ = user;
    passwd_ = passwd;
    database_ = database;

    for (int i = 0 ; i < max_conn_count; ++i) {
        MYSQL* mysql = NULL;
        mysql = mysql_init(mysql);
        if (mysql == NULL) {
            // false
            printf("mysql_init failed\n");
            exit(1);
        }
        mysql = mysql_real_connect(mysql, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), port_, NULL, 0);
        if (mysql == NULL) {
            printf("mysql_real_connect failedm, host: %s, port:%d, user: %s, passwd: %s, database: %s\n", host_.c_str(), 
                    port_, user_.c_str(), passwd_.c_str(), database_.c_str());
            exit(1);
        }
        conn_list_.push_back(mysql);
        ++free_conn_count_;

    }
    sem_ = Sem(free_conn_count_);
    max_conn_count_ = max_conn_count;
}

MYSQL* MysqlConnPool::GetConn() {
    MYSQL* conn = nullptr;
    if (conn_list_.size() == 0) {
        printf("db pool conn num is 0\n");
        return nullptr;
    }
    sem_.Wait();
    locker_.Lock();
    conn = conn_list_.front();
    conn_list_.pop_front();
    --free_conn_count_;
    ++cur_conn_count_;
    locker_.UnLock();
    return conn;

}

bool MysqlConnPool::ReleaseConn(MYSQL* conn) {
    if (conn == nullptr) {
        printf("release conn is null\n");
        return false;
    }
    locker_.Lock();
    conn_list_.push_back(conn);
    ++free_conn_count_;
    --cur_conn_count_;
    locker_.UnLock();
    sem_.Post();
    return true;
}

void MysqlConnPool::DestroyPool() {
    locker_.Lock();
    if (conn_list_.size() > 0) {
        for (auto conn : conn_list_) {
            mysql_close(conn);
        }
        free_conn_count_ = 0;
        cur_conn_count_ = 0;
        conn_list_.clear();
    }
    locker_.UnLock();
} 

int MysqlConnPool::get_free_count() {
    return free_conn_count_;
}

MysqlConnPool::MysqlConnPool() {
    cur_conn_count_ = 0;
    free_conn_count_ = 0;
}


MysqlConnPool::~MysqlConnPool() {
    DestroyPool();
}


bool MyQuery(MYSQL* conn, const std::string& sql, std::vector<std::vector<uint8_t>>& data) {
    int ret = mysql_query(conn, sql.c_str());
    if (ret != 0) {
        printf("mysql query error: %s\n", mysql_error(conn));
        return false;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        printf("mysql query error: %s\n", mysql_error(conn));
        return false;
    } else {
        MYSQL_ROW row;
        int num_fields = mysql_num_fields(result);

        while (row = mysql_fetch_row(result)) {
            std::vector<uint8_t> row_data;
            for (int i = 0; i < num_fields; i++) {
                if (row[i] != nullptr) {
                    row_data.insert(row_data.end(), row[i], row[i] + mysql_fetch_lengths(result)[i]);
                }
            }
            data.push_back(row_data);
        }
    }
    mysql_free_result(result);
    return true;
}

bool MyUpdate(MYSQL* conn, const std::string& sql) {
    return true;
}

