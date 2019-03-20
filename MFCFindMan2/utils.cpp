#define _CRT_SECURE_NO_WARNINGS 
#include "utils.h"
#include <iostream>
using namespace std;
int Calculat_FlieLength(const char * path)
{
	FILE *fd = NULL;
	int size = 0;

	fd = fopen(path, "rb");
	if (fd == NULL)
	{
		cout << "Calculat_FlieLength file open is err" << endl;
		return -1;
	}
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	fclose(fd);
	return size;
}

int Read_Image(const char * path, char * out)
{
	FILE *fd = NULL;
	int length = 0;
	int ret = 0;
	int i = 0;

	fd = fopen(path, "rb");
	if (fd == NULL)
	{
		cout << "Read_Image open file err" << endl;
	}
	fseek(fd, 0, SEEK_END);
	length = ftell(fd);
	rewind(fd);

	ret = fread(out, 1, length,fd);
	if (ret == 0)
	{
		cout << "Reading error" << endl;
	}
	fclose(fd);

	return ret;
}
