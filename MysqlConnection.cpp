#include "MysqlConnection.h"


MysqlConnection::MysqlConnection(std::string host, std::string user, std::string passwd, std::string database) {
    if (mysql_init(m_mysql) == NULL) {
        printf("mysql init error\n");
    }
    m_host = host;
    m_user = user;
    m_passwd = passwd;
    m_database = database;
    if (!m_mysql) {
        // Connect();
    } else {
        printf("mysql is null\n");
    }
}

MysqlConnection::~MysqlConnection() {
    mysql_close(m_mysql);   
}


void MysqlConnection::Connect() {
    if (!mysql_real_connect(m_mysql, m_host.c_str(), m_user.c_str(), m_passwd.c_str(), m_database.c_str(), 0, NULL, 0)) {
        printf("mysql connect failed\n");
    } else {
        m_success = true;
    }
}



