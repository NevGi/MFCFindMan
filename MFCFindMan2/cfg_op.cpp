#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "cfg_op.h"
#include "trim_space.h"
#include <iostream>

#define MAXLIEN 2048
//获取配置项
int GetCfgItem(char * pFileName/*in*/, char * pKey/*in*/, char * pValue/*in out*/, int * ValueLen/*out*/)
{
	//
	int ret = 0;
	FILE * fp = NULL;
	char lineBuf[2048];
	char * ptmp = NULL;

	fp=fopen(pFileName, "r");
	if (fp == NULL)
	{

		ret = -1;
		return ret;
	}

	
	while (!feof(fp))
	{
		memset(lineBuf, 0, sizeof(lineBuf));
		fgets(lineBuf,MAXLIEN,fp);


		ptmp = strchr(lineBuf, '=');
		if (ptmp == NULL)
		{
			continue;
		}

		ptmp=strstr(lineBuf, pKey);
		if (ptmp == NULL)//所在行是不是有p
		{
			continue;

		}

		ptmp += strlen(pKey);//mykey1 = fdsfsda ==> = fdsfsda

		ptmp = strchr(ptmp, '=');
		if (ptmp == NULL)
		{
			continue;

		}
		ptmp += 1;

		//

		trimSpace(ptmp, pValue);

		


	}
	*ValueLen = strlen(pValue);
	return 0;
}

//写配置项
//实现流程
//循环读每一行，检查key配置项是否存在，若存在修改对应value值
//难点：如何修改文件流中的值
int WriteCfgItem(char *pFIleName/*in*/, char *pKey/*in*/, char *pValue/*in*/, int ValueLen/*in*/)
{
	int rv = 0, iTag = 0, lenth = 0;
	FILE *fp = NULL;
	char lineBuf[MAXLIEN];
	char *pTmp = NULL, *pBegin = NULL, *pEnd = NULL;
	char filebuf[1024 * 8] = { 0 };

	if (pFIleName == NULL || pKey == NULL || pValue == NULL)
	{
		rv = -1;
		printf("SetCfgItem() err. param err \n");
		goto END;

	}

	fp = fopen(pFIleName, "r+");
	if (fp == NULL)
	{
		rv = -2;
		printf("fopen() err. \n");


	}

	if (fp == NULL)
	{
		fp = fopen(pFIleName, "w+");
		if (fp == NULL)
		{
			rv = -3;
			printf("fopen() err. \n");
			goto END;

		}

	}

	fseek(fp, 0L, SEEK_END);//把文件指针从0位置开始，移到文件末尾
							//获取文件长度

	lenth = ftell(fp);


	fseek(fp, 0L, SEEK_SET);

	if (lenth > 1024 * 8)
	{
		rv = -3;
		printf("文件超过1024*8,nunsupport");
		goto END;

	}

	while (!feof(fp))
	{
		//读每一行
		memset(lineBuf, 0, sizeof(lineBuf));
		pTmp = fgets(lineBuf, MAXLIEN, fp);
		if (pTmp == NULL)
		{
			break;

		}

		//key关键字是否在本行
		pTmp = strstr(lineBuf, pKey);
		if (pTmp == NULL)//key关键字不在本行，copy到filebuf中
		{
			strcat(filebuf, lineBuf);
			continue;

		}
		else //key关键字在本行中，替换旧的行，再copy到filebuf中
		{
			sprintf(lineBuf, "%s=%s\n", pKey, pValue);
			strcat(filebuf, lineBuf);
			//若存在key
			iTag = 1;

		}

	}

	//若关键字不存在追加
	if (iTag == 0)
	{
		fprintf(fp, "%s = %s\n", pKey, pValue);

	}
	else//若key关键字 存在 则重新创建文件
	{
		if (fp != NULL)
		{
			fclose(fp);
			fp = NULL;

		}
		fp = fopen(pFIleName, "w+");
		if (fp == NULL)
		{

			rv = -4;
			printf("fopen() err. \n");
			goto END;



		}
		fputs(filebuf, fp);

	}

END:
	if (fp != NULL)
	{
		fclose(fp);
	}
	return rv;
		
	

	return 0;
}
