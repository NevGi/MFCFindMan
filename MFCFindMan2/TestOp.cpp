#define _CRT_SECURE_NO_WARNINGS
#include "TestOp.h"
#include<iostream>
#include<string.h>
#include"utils.h"
#include"face.h"
#include<json/json.h>
#include"DaoUtils.h"


#define INFOLEN 50

int InputAnCheck(const char * path, const char * group)
{

	int ret = 0;
	char * pathdata = NULL;
	int len = 0;
	int fread_len = 0;

	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);

	//���ͼƬ �Ƿ�ϸ�
	len = Calculat_FlieLength(path);
	if (len < 0)
	{
		std::cout << "read image length erro" << std::endl;
		return len;
	}

	pathdata = (char*)malloc(sizeof(char)*len);
	if (pathdata == NULL)
	{
		std::cout << "image malloc is error" << std::endl;
		return -2;
	}

	fread_len = Read_Image(path, pathdata);
	if (fread_len != len)
	{
		std::cout << " read image error " << std::endl;
		free(pathdata);
		return -3;
	}

	//У���ȡ�Ƿ�ɹ�
	std::cout << len << "++++++" << fread_len << std::endl;

	Json::Value result;
	std::string image = aip::base64_encode(pathdata, fread_len);
	std::string image_type = "BASE64";
	// �����������
	result = client.detect(image, image_type, aip::null);
	//std::cout << result << std::endl;

	if (result["result"].isNull())
	{
		std::cout << "image dont has face" << std::endl;
		free(pathdata);
		return -4;
	}


	char src[50] = { 0 };
	strcpy(src, path);

	for (int i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == '\\' || src[i] == ':' || src[i] == '.'||src[i]=='('||src[i]==')')
		{
			src[i] = '_';

		}
	}

	//std::cout << ss.str() << std::endl;
	//base 64���� Ȼ�󴫵ݸ��ٶ�AI
	std::string group_id = group;
	std::string user_id = src;
	// ��������ע��
	result = client.user_add(image, image_type, group_id, user_id, aip::null);
	//result = client.user_add(image, image_type, group_id, user_id, options);
	//������������
	//std::cout << result << std::endl;

	if (result["result"].isNull())
	{
		std::cout << "image is exist or other error" << std::endl;
		free(pathdata);
		return -5;
	}

	std::string face_token = result["result"]["face_token"].asString();
	//std::cout << face_token << std::endl;
	char src2[50] = { 0 };
	strcpy(src2, path);
	
	for (int i = 0; src2[i] != '\0'; i++)
	{
		if (src2[i] == '\\')
		{
			src2[i] = '/';

		}
	}

	//¼�����ݿ� ���� face_token name age
	MYSQL* mysql;
	//��ʼ���������ݿ�
	ret = InitMsql(&mysql,"localhost", "root", "kzh971104", "xs_db");
	if (ret != 0)
	{
		return -6;
	}

	//�����ݿ��������
	char sqlbuf[1024] = { 0 };

	//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

	sprintf(sqlbuf, "insert into userinfo (`face_token`,`path`,`user`,`group`) values ('%s','%s','%s','%s')", \
		face_token.c_str(), src2, src,group);

	ret = InSertInfo(mysql, sqlbuf);
	if (ret != 0)
	{
		return -7;
	}
	
	DeMysql(mysql);
	free(pathdata);
	return 0;
}
//int MatchUse(const char * path,std::string group,PerSon& person)
//{
//
//	int ret = 0;
//	char * pathdata = NULL;
//	int len = 0;
//	int fread_len = 0;
//
//	//��ʼ���ٶ�AI���� 
//	std::string app_id = "15636070";
//	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
//	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
//	aip::Face client(app_id, api_key, secret_key);
//
//	//���ͼƬ �Ƿ�ϸ�
//	len = Calculat_FlieLength(path);
//	if (len < 0)
//	{
//		std::cout << "read image length erro" << std::endl;
//		return len;
//	}
//
//	pathdata = (char*)malloc(sizeof(char)*len);
//	if (pathdata == NULL)
//	{
//		std::cout << "image malloc is error" << std::endl;
//		return -2;
//	}
//
//	fread_len = Read_Image(path, pathdata);
//	if (fread_len != len)
//	{
//		std::cout << " read image error " << std::endl;
//		free(pathdata);
//		return -3;
//	}
//
//	//У���ȡ�Ƿ�ɹ�
//	std::cout << len << "++++++" << fread_len << std::endl;
//
//	Json::Value result;
//	std::string image = aip::base64_encode(pathdata, fread_len);
//	std::string image_type = "BASE64";
//	// �����������
//	result = client.detect(image, image_type, aip::null);
//	//std::cout << result << std::endl;
//
//	if (result["result"].isNull())
//	{
//		std::cout << "image dont has face" << std::endl;
//		free(pathdata);
//		return -4;
//	}
//
//	//������������
//	//�ַ���ƴ��
//	std::string group_id_list = group;
//	result = client.search(image, image_type, group_id_list, aip::null);
//
//	if (result["result"].isNull())
//	{
//		std::cout << "dont find match user the database dont have person" << std::endl;
//		free(pathdata);
//		return -5;
//	}
//
//	//std::cout << result << std::endl;
//
//	//�����ȶԷ���ֵ ��� ���� 80��ô �ȶԳɹ���� user_info
//	Json::Value out = result["result"];
//	Json::Value arrayobj = out["user_list"];
//	float score = 0;
//	char* group_id = NULL;
//	char* user_id = NULL;
//
//	//�ȶ����ƶȸ���80��ͼƬ������û���Ϣ
//	for (int i = 0; i < arrayobj.size(); i++)
//	{
//		score = arrayobj[i]["score"].asFloat();
//		if (score >= 80)
//		{
//			
//			group_id = (char*)malloc((strlen(arrayobj[i]["group_id"].asCString()) + 1));
//			user_id = (char*)malloc((strlen(arrayobj[i]["user_id"].asCString()) + 1));
//			strcpy(group_id, arrayobj[i]["group_id"].asCString());
//			strcpy(user_id, arrayobj[i]["user_id"].asCString());
//			
//			ret = GetUserInfo(group_id, user_id, &person);
//			
//			free(group_id);
//			free(user_id);
//			break;
//		}
//
//		ret = -6;
//	}
//
//	
//
//	//std::cout << arrayobj << std::endl;
//	//std::cout << out << std::endl;
//
//	free(pathdata);
//
//	if (ret == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return ret;
//	}
//}
int MatchUse(const char * path, std::string group, std::vector<PerSon>* persons)
{

	int ret = 0;
	char * pathdata = NULL;
	int len = 0;
	int fread_len = 0;

	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);

	//���ͼƬ �Ƿ�ϸ�
	len = Calculat_FlieLength(path);
	if (len < 0)
	{
		std::cout << "read image length erro" << std::endl;
		return len;
	}

	pathdata = (char*)malloc(sizeof(char)*len);
	if (pathdata == NULL)
	{
		std::cout << "image malloc is error" << std::endl;
		return -2;
	}

	fread_len = Read_Image(path, pathdata);
	if (fread_len != len)
	{
		std::cout << " read image error " << std::endl;
		free(pathdata);
		return -3;
	}

	//У���ȡ�Ƿ�ɹ�
	std::cout << len << "++++++" << fread_len << std::endl;

	Json::Value result;
	std::string image = aip::base64_encode(pathdata, fread_len);
	std::string image_type = "BASE64";
	// �����������
	result = client.detect(image, image_type, aip::null);
	//std::cout << result << std::endl;

	if (result["result"].isNull())
	{
		std::cout << "image dont has face" << std::endl;
		free(pathdata);
		return -4;
	}




	//������������
	//�ַ���ƴ��
	std::string group_id_list = group;

	// ����п�ѡ����
	std::map<std::string, std::string> options;
	options["max_user_num"] = "10";

	// ������������������
	result = client.search(image, image_type, group_id_list, options);

	//result = client.search(image, image_type, group_id_list, aip::null);

	if (result["result"].isNull())
	{
		std::cout << "dont find match user the database dont have person" << std::endl;
		free(pathdata);
		return -5;
	}

	//std::cout << result << std::endl;

	//�����ȶԷ���ֵ ��� ���� 80��ô �ȶԳɹ���� user_info
	Json::Value out = result["result"];
	Json::Value arrayobj = out["user_list"];
	float score = 0;
	char* group_id = NULL;
	char* user_id = NULL;

	//�ȶ����ƶȸ���80��ͼƬ������û���Ϣ
	for (int i = 0; i < arrayobj.size(); i++)
	{
		score = arrayobj[i]["score"].asFloat();
		if (score >= 80)
		{
			PerSon person;

			group_id = (char*)malloc((strlen(arrayobj[i]["group_id"].asCString()) + 1));
			user_id = (char*)malloc((strlen(arrayobj[i]["user_id"].asCString()) + 1));
			strcpy(group_id, arrayobj[i]["group_id"].asCString());
			strcpy(user_id, arrayobj[i]["user_id"].asCString());
			person.score = score;

			ret = GetUserInfo(group_id, user_id, &person);

			(*persons).push_back(person);
			free(group_id);
			free(user_id);
		}

	}

	//std::cout << arrayobj << std::endl;
	//std::cout << out << std::endl;

	free(pathdata);

	if (ret == 0)
	{
		return 0;
	}
	else
	{
		return ret;
	}
}
int QueryUser(const char* name,char** info)
{
	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);


	Json::Value result;
	std::string user_id = name;
	std::string group_id = "group1";

	result = client.user_get(user_id, group_id, aip::null);

	if (result["result"].isNull())
	{
		std::cout << "dont find your info please comfirm" << std::endl;
		return -5;
	}

	Json::Value out = result["result"];
	Json::Value arrayobj = out["user_list"];

	//strncpy(info, arrayobj[0]["user_info"].asCString(),strlen(arrayobj[0]["user_info"].asCString())+1);
	//memcpy(info, arrayobj[0]["user_info"].asCString(), (strlen(arrayobj[0]["user_info"].asCString())-1));
	char* info1 = (char*)malloc((strlen(arrayobj[0]["user_info"].asCString()) + 1));
	strcpy(info1, arrayobj[0]["user_info"].asCString());

	*info = info1;



	return 0;
	//std::cout << result << std::endl;

}
int GetGroup(char*** p,int * len)
{
	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);

	Json::Value result;

	// �������б��ѯ
	result = client.group_getlist(aip::null);
	//std::cout << result << std::endl;

	if (result["result"].isNull())
	{
		return -1;
	}
	//��ȡ��json ����
	Json::Value out = result["result"];
	Json::Value arrayobj = out["group_id_list"];

	char** a = (char**)malloc(sizeof(char*)*arrayobj.size());

	for (int i = 0; i < arrayobj.size(); i++)
	{
		//�����ַ�ָ�뱣�� �����ַ�����
		a[i] = (char*)malloc(strlen(arrayobj[i].asCString()) + 1);
		strcpy(a[i], arrayobj[i].asCString());
		
	}
	*len = arrayobj.size();

	*p = a;

/*	for (int i = 0; i < arrayobj.size(); i++)
	{
		free(a[i]);
	}
	free(a)*/;

	return 0;
}
int UpdateInfo(const PerSon* person)
{
	int ret = 0;
	char * pathdata = NULL;
	int len = 0;
	int fread_len = 0;

	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);

	//���ͼƬ �Ƿ�ϸ�
	len = Calculat_FlieLength(person->path);
	if (len < 0)
	{
		std::cout << "read image length erro" << std::endl;
		return len;
	}

	pathdata = (char*)malloc(sizeof(char)*len);
	if (pathdata == NULL)
	{
		std::cout << "image malloc is error" << std::endl;
		return -2;
	}

	fread_len = Read_Image(person->path, pathdata);
	if (fread_len != len)
	{
		std::cout << " read image error " << std::endl;
		free(pathdata);
		return -3;
	}

	//У���ȡ�Ƿ�ɹ�
	std::cout << len << "++++++" << fread_len << std::endl;

	Json::Value result;
	std::string image = aip::base64_encode(pathdata, fread_len);
	std::string image_type = "BASE64";
	// �����������
	result = client.detect(image, image_type, aip::null);
	//std::cout << result << std::endl;

	if (result["result"].isNull())
	{
		std::cout << "image dont has face" << std::endl;
		free(pathdata);
		return -4;
	}

	std::string group_id= person->group;
	std::string user_id = person->user;

	// ������������������
	// ������������
	result = client.user_update(image, image_type, group_id, user_id, aip::null);
	if (result["result"].isNull())
	{
		std::cout << "image is exist or other error" << std::endl;
		free(pathdata);
		return -5;
	}

	std::string face_token = result["result"]["face_token"].asString();
	//std::cout << face_token << std::endl;
	char src2[50] = { 0 };
	strcpy(src2, person->path);

	for (int i = 0; src2[i] != '\0'; i++)
	{
		if (src2[i] == '\\')
		{
			src2[i] = '/';

		}
	}

	//¼�����ݿ� ���� face_token name age
	MYSQL* mysql;
	//��ʼ���������ݿ�
	ret = InitMsql(&mysql, "localhost", "root", "kzh971104", "xs_db");
	if (ret != 0)
	{
		return -6;
	}

	//�����ݿ��������
	char sqlbuf[1024] = { 0 };

	//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

	sprintf(sqlbuf, "update userinfo  set `face_token`='%s',`path`='%s',`name`='%s',`age`=%d where `user`='%s'", \
		face_token.c_str(), src2,person->name,person->age,person->user);

	ret = InSertInfo(mysql, sqlbuf);
	if (ret != 0)
	{
		return -7;
	}

	DeMysql(mysql);

	free(pathdata);
	return 0;
}
int GetUsers(const char * group,int* a,char*** p,int start,int end)
{


	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);
	Json::Value result;
	std::string group_id = group;
	// ���û�ȡ�û��б�
	result = client.group_getusers(group_id, aip::null);

	// ����п�ѡ����
	std::map<std::string, std::string> options;

	char tstart[10];
	char tend[10];
	memset(tstart, 0, sizeof(start));
	memset(tend, 0, sizeof(tend));

	options["start"] = _itoa(start,tstart,10);
	options["length"] = _itoa(end,tend,10);

	// ���������û�ȡ�û��б�
	result = client.group_getusers(group_id, options);
	if (result["result"].isNull())
	{
		std::cout << "dont find anyuser in this group" << std::endl;
		return -1;
	}
	Json::Value out = result["result"];
	Json::Value arrayobj = out["user_id_list"];

	char ** info = (char**)malloc(sizeof(char*)*(arrayobj.size()));
	for (int i = 0; i < arrayobj.size(); i++)
	{
		info[i] = (char*)malloc((strlen(arrayobj[i].asCString()) + 1));
		strcpy(info[i], arrayobj[i].asCString());
		std::cout << info[i];

	}

	*a = arrayobj.size();
	*p = info;
	return 0;
}
int GetUserInfo(const char* group, const char* user, PerSon* person)
{
	////��ʼ���ٶ�AI���� 
	//std::string app_id = "15636070";
	//std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	//std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	//aip::Face client(app_id, api_key, secret_key);

	////Json::Value result;
	////std::string user_id = "group1";
	////std::string group_id = "user1";
	////std::cout << group << std::endl;
	////std::cout << user << std::endl;

	//std::cout << "�����û���Ϣ��ѯ" << std::endl;

	//Json::Value result;

	//std::string user_id = user;

	//std::string group_id = group;

	//// �����û���Ϣ��ѯ
	//result = client.user_get(user_id, group_id, aip::null);

	//char * info1 = NULL;

	//if (result["result"].isNull())
	//{
	//	return -1;
	//}

	////��ȡ��Ϣ
	//Json::Value out = result["result"];
	//Json::Value arrayobj = out["user_list"];
	//Json::Value person = arrayobj[0];
	//info1 = (char*)malloc(strlen(person["user_info"].asCString()) + 1);
	//strcpy(info1, person["user_info"].asCString());

	int ret = 0;

	//�����ݿ��ȡ�û���Ϣ
	MYSQL* mysql;
	char age[10] = { 0 };
	//��ʼ���������ݿ�
	ret = InitMsql(&mysql, "localhost", "root", "kzh971104", "xs_db");
	if (ret != 0)
	{
		DeMysql(mysql);
		return -6;
	}
	char sqlbuf[500] = { 0 };

	//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

	sprintf(sqlbuf, "select * from `userinfo` where `group`='%s' and `user`='%s'", group, user);

	ret = SelUser(mysql, sqlbuf,(*person));
	if (ret != 0)
	{
		DeMysql(mysql);
		return -7;
	}


	DeMysql(mysql);
	return 0;
}
int	CreateGroup(const char * group)
{
	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);
	Json::Value result;
	std::string group_id = group;
	// ���ô����û���
	result = client.group_add(group_id, aip::null);

	if (result["result"]["error_msg"].isNull())
	{
		return 0;
	}

	return -1;
}
int DelGroup(const char * group)
{

	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);
	std::stringstream ss;
	ss << group;


	Json::Value result;

	std::string group_id = ss.str();

	// ����ɾ���û���
	result = client.group_delete(group_id, aip::null);


	std::cout << result << std::endl;

	return 0;
}
int DelUser(const char * group, const char * user)
{
	//��ʼ���ٶ�AI���� 
	std::string app_id = "15636070";
	std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	aip::Face client(app_id, api_key, secret_key);


	Json::Value result;
	std::string group_id = group;
	std::string user_id = user;
	// ����ɾ���û�
	result = client.user_delete(group_id, user_id, aip::null);

	if (!(result["result"]["error_msg"].isNull()))
	{
		
		return -1;
	}

	//�����ݿ�ɾ��



	return 0;
}
int MatchUserInfo(const char* user, PerSon* person)
{
	////��ʼ���ٶ�AI���� 
	//std::string app_id = "15636070";
	//std::string api_key = "AfhYgV2W5Ry5F4y2Zb3dGmMp";
	//std::string secret_key = "0RyxyGjw1HVaSZGF2KN6VlF045wFMb4e";
	//aip::Face client(app_id, api_key, secret_key);

	////Json::Value result;
	////std::string user_id = "group1";
	////std::string group_id = "user1";
	////std::cout << group << std::endl;
	////std::cout << user << std::endl;

	//std::cout << "�����û���Ϣ��ѯ" << std::endl;

	//Json::Value result;

	//std::string user_id = user;

	//std::string group_id = group;

	//// �����û���Ϣ��ѯ
	//result = client.user_get(user_id, group_id, aip::null);

	//char * info1 = NULL;

	//if (result["result"].isNull())
	//{
	//	return -1;
	//}

	////��ȡ��Ϣ
	//Json::Value out = result["result"];
	//Json::Value arrayobj = out["user_list"];
	//Json::Value person = arrayobj[0];
	//info1 = (char*)malloc(strlen(person["user_info"].asCString()) + 1);
	//strcpy(info1, person["user_info"].asCString());

	int ret = 0;

	//�����ݿ��ȡ�û���Ϣ
	MYSQL* mysql;
	char age[10] = { 0 };
	//��ʼ���������ݿ�
	ret = InitMsql(&mysql, "localhost", "root", "kzh971104", "xs_db");
	if (ret != 0)
	{
		DeMysql(mysql);
		return -6;
	}
	char sqlbuf[500] = { 0 };

	//strcpy(sqlbuf, "insert into `userinfo`(`face_token`,`path`,`user`,`group`,`name`,`age`) values ('fdsaf', 'fadf', 'fad', 'fda', 'fad', 8)");

	sprintf(sqlbuf, "select * from `userinfo` where`user`='%s'", user);

	ret = SelUser(mysql, sqlbuf, (*person));
	if (ret != 0)
	{
		DeMysql(mysql);
		return -7;
	}


	DeMysql(mysql);
	return 0;
}