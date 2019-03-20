#define _CRT_SECURE_NO_WARNINGS
#include "DaoUtils.h"
#include <iostream>
int InitMsql(MYSQL** outmysql,const char* localhost,const char * user,const char * pass,const char * dbname)
{

	MYSQL *mysql = NULL;
	int ret = 0;
	//初始化
	//MYSQL *mysql_init(MYSQL *mysql) 
	//unsigned int mysql_errno(MYSQL *mysql) 
	mysql = mysql_init(NULL);
	if (mysql == NULL) {
		ret = mysql_errno(mysql);
		std::cout << ret << std::endl;
		return ret;
	}
	printf("init ok...\n");
	//连接数据库
	//MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, 		const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag) 
	mysql = mysql_real_connect(mysql, localhost, user, pass, dbname, 0, NULL, 0);
	if (mysql == NULL) {
		ret = mysql_errno(mysql);
		std::cout << ret << std::endl;
		return ret;
	}
	//设置查询字符集
	ret = mysql_query(mysql, "set names utf8");
	if (ret != 0) {
		printf("mysql_query err: %d\n", ret);
		return ret;
	}

	*outmysql = mysql;

	return 0;
}
int InSertInfo(MYSQL* mysql,const char* sqlbuf)
{
	int ret = 0;

	ret = mysql_query(mysql, sqlbuf);
	if (ret != 0) {
		printf("mysql_query err: %d\n", ret);
		return ret;
	}

	return 0;
}
int SelUser(MYSQL * mysql, const char * sqlbuf, PerSon& person)
{
	int ret = 0;
	int num = 0;
	//执行SQL语句
	ret = mysql_query(mysql, sqlbuf);
	if (ret != 0) {
		printf("mysql_query err: %d\n", ret);
		return ret;
	}

	//获取列数
	num = mysql_field_count(mysql);



	//获取结果集
	MYSQL_RES *result = NULL;
	result = mysql_store_result(mysql);
	if (result == NULL) {
		ret = mysql_errno(mysql);
		printf("mysql_store_result err: %d\n", ret);
		return ret;
	}

	//解析结果集，提取数据  
	MYSQL_ROW row;			//typedef char ** MYSQL_ROW;
	row = mysql_fetch_row(result);
	if (row == NULL)
	{
		return -1;
	}

	for (int i = 0; i < num; i++) {
		if (row[i] != NULL)
		{

			if (i == 1)
			{

				strncpy(person.face_token, row[i], strlen(row[i]) + 1);

			}
			else if (i == 2)
			{
				strncpy(person.path, row[i], strlen(row[i]) + 1);
			}
			else if (i == 3)
			{
				strncpy(person.user, row[i], strlen(row[i]) + 1);

			}
			else if (i == 4)
			{
				strncpy(person.group, row[i], strlen(row[i]) + 1);
			}
			else if (i == 5)
			{
				strncpy(person.name, row[i], strlen(row[i]) + 1);
			}
			else if (i == 6)
			{
				person.age = atoi(row[i]);

			}

		}

	}

	//释放结果集 
	mysql_free_result(result);

	return 0;
}
int DeMysql(MYSQL * mysql)
{
	//关闭
	mysql_close(mysql);
	return 0;
}

