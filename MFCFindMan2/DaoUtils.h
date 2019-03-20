#pragma once
#include"mysql.h"
#include "PerSon.h"
int InitMsql(MYSQL** mysql, const char * localhost, const char* user, const char* pass, const char* dbname);
int InSertInfo(MYSQL* mysql, const char *sqlbuf);
int SelUser(MYSQL* mysql, const char* sqlbuf, PerSon& PerSon);
int DeMysql(MYSQL* mysql);