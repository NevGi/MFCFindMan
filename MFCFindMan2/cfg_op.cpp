#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "cfg_op.h"
#include "trim_space.h"
#include <iostream>

#define MAXLIEN 2048
//��ȡ������
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
		if (ptmp == NULL)//�������ǲ�����p
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

//д������
//ʵ������
//ѭ����ÿһ�У����key�������Ƿ���ڣ��������޸Ķ�Ӧvalueֵ
//�ѵ㣺����޸��ļ����е�ֵ
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

	fseek(fp, 0L, SEEK_END);//���ļ�ָ���0λ�ÿ�ʼ���Ƶ��ļ�ĩβ
							//��ȡ�ļ�����

	lenth = ftell(fp);


	fseek(fp, 0L, SEEK_SET);

	if (lenth > 1024 * 8)
	{
		rv = -3;
		printf("�ļ�����1024*8,nunsupport");
		goto END;

	}

	while (!feof(fp))
	{
		//��ÿһ��
		memset(lineBuf, 0, sizeof(lineBuf));
		pTmp = fgets(lineBuf, MAXLIEN, fp);
		if (pTmp == NULL)
		{
			break;

		}

		//key�ؼ����Ƿ��ڱ���
		pTmp = strstr(lineBuf, pKey);
		if (pTmp == NULL)//key�ؼ��ֲ��ڱ��У�copy��filebuf��
		{
			strcat(filebuf, lineBuf);
			continue;

		}
		else //key�ؼ����ڱ����У��滻�ɵ��У���copy��filebuf��
		{
			sprintf(lineBuf, "%s=%s\n", pKey, pValue);
			strcat(filebuf, lineBuf);
			//������key
			iTag = 1;

		}

	}

	//���ؼ��ֲ�����׷��
	if (iTag == 0)
	{
		fprintf(fp, "%s = %s\n", pKey, pValue);

	}
	else//��key�ؼ��� ���� �����´����ļ�
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
