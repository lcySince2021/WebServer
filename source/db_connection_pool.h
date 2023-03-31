#ifndef _DB_CONNECTION_POOL_H_
#define _DB_CONNECTION_POOL_H_
#include <iostream>
#include <queue>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <mysql/mysql.h>
#include "locker.h"
#include <list>
class MysqlConnPool {
public:
    static MysqlConnPool* GetInstance();
    void Init(const std::string& host, int port, const std::string& user, const std::string& passwd, const std::string& database, int MaxConnCount);
    MYSQL* GetConn();
    bool ReleaseConn(MYSQL* conn);
    void DestroyPool();
    int GetFree();

private:
    MysqlConnPool();
    ~MysqlConnPool();

public:
    std::string host_;
    int port_;
    std::string user_;
    std::string passwd_;
    std::string database_;
private:
    int free_conn_count_;
    int cur_conn_count_;
    int max_conn_count_;
    std::list<MYSQL*> conn_list_;
    Locker locker_;
    Sem sem_;
};

bool MyQuery(MYSQL* conn, const std::string& sql, char* data);


#endif
