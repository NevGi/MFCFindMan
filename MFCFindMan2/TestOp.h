#pragma once
#include<string>
#include<vector>
#include"PerSon.h"

int InputAnCheck(const char * path,const char * group);
//int MatchUse(const char* path,std::string group, PerSon& person);
int MatchUse(const char* path, std::string group,std::vector<PerSon>* persons);
int QueryUser(const char* name,char** info);
int GetGroup(char*** p,int* len);
int UpdateInfo(const PerSon* person);
int GetUsers(const char * group,int* a,char*** p,int start,int end);
int GetUserInfo(const char* group, const char* user,PerSon* person);
int CreateGroup(const char* group);
int DelGroup(const char * group);
int DelUser(const char* group, const char* user);
int MatchUserInfo(const char* user, PerSon* person);