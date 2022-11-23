#include "mysql_connection.h"


MysqlConnection::MysqlConnection() {
    printf("create mysql connection\n");
}

MysqlConnection::~MysqlConnection() {
    mysql_close(&mysql_);   
    delete field_;
    delete result_;
    printf("delete mysql connection\n");
}


bool MysqlConnection::Init() {
    if (!mysql_init(&mysql_)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql init failed\n");
        return false;
    }
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    } 
    is_inited_ = true;
    return true;
}

bool MysqlConnection::Init(std::string host, int port, std::string user, std::string passwd, std::string database) {
    host_ = host;
    port_ = port;
    user_ = user;
    passwd_ = passwd;
    database_ = database;
    if (!mysql_init(&mysql_)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql init failed\n");
        return false;
    }
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    } 
    is_inited_ = true;
    return true;
}

bool MysqlConnection::ReConnect() {
    if (!mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), database_.c_str(), 3306, NULL, 0)) {
        std::cout << mysql_error(&mysql_) << std::endl;
        printf("mysql connect failed\n");
        return false;
    }
    return true;
}

bool MysqlConnection::Update(const std::string& sql) {
    if (!is_inited_) {
        printf("not init\n");
        return false;
    }
    if (mysql_query(&mysql_, sql.c_str())) {
        std::cout << mysql_error(&mysql_) << ", sql:" << sql << std::endl;
        return false;
    } else {
        std::cout << mysql_error(&mysql_) << ", sql:" << sql << std::endl;

    }
    return true;
}

bool MysqlConnection::Query(const std::string& sql) {
    if (!is_inited_) {
        printf("not init\n");
        return false;
    }
    if (mysql_query(&mysql_, sql.c_str())) {
        std::cout << mysql_error(&mysql_) << ", sql:" << sql << std::endl;
        return false;
    }
    result_ = mysql_store_result(&mysql_);
    if (!result_) {
        std::cout << mysql_error(&mysql_) << ", sql:" << sql << std::endl;
    }
    int num;
	num = mysql_num_fields(result_);  //返回字段个数
	for( int i = 0; i < num; i++ ) {
		field_ = mysql_fetch_field_direct(result_, i );  //返回字段类型
		std::cout << field_->name << "\t\t";  //输出字段名
        std::cout << std::endl;
	}
    while(row_ = mysql_fetch_row(result_), row_) {
		for( int i = 0; i < num; i++ ) {
			std::cout << row_[i] << "\t\t";
		}
		std::cout << std::endl;
	}
    return true;
}

