#ifndef _DB_CONNECTION_H_
#define _DB_CONNECTION_H_
#include <mysql/mysql.h>
#include <iostream>
#include <string>

class DbConnection {
public:
    ~DbConnection() {
        printf("destory\n");
    }
    static DbConnection& get_instance() {
        static DbConnection instance;
        return instance;
    }
private:
    DbConnection() { 
        printf("created\n");
    }

public:
    std::string m_host; // host
    int m_port; // port
    std::string m_pwd; // password
    std::string m_usernmae; // username
    std::string database; // database
};


#endif
