#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include"bigdata_calculate.h"

void cal::carry_bit()
{
	for (int i = 0; i<real_len1; i++)
	{
		int a = buf[real_len1 - i] / 10;
		buf[real_len1 - i] = buf[real_len1 - i] % 10;
		buf[real_len1 - i - 1] += a;
	}
	if (flen1>flen2)
	{
		for (int i = 0; i<flen1 - 1; i++)
		{
			int a = buf[real_len1 + 1 + flen1 - i] / 10;
			buf[real_len1 + 1 + flen1 - i] = buf[real_len1 + 1 + flen1 - i] % 10;
			buf[real_len1 + 1 + flen1 - i - 1] += a;
		}
		buf[real_len1 + 2 + flen1] = '\0';
	}
	else
	{
		for (int i = 0; i<flen2 - 1; i++)
		{
			int a = buf[real_len1 + 1 + flen2 - i] / 10;
			buf[real_len1 + 1 + flen2 - i] = buf[real_len1 + 1 + flen2 - i] % 10;
			buf[real_len1 + 1 + flen2 - i - 1] += a;
		}
		buf[real_len1 + 2 + flen2] = '\0';
	}
	int a = buf[real_len1 + 2] / 10;
	buf[real_len1 + 2] = buf[real_len1 + 2] % 10;
	buf[real_len1] += a;
}

void cal::buftores()
{
	int i = 0;
	while (buf[i] == 0)
	{
		i++;
	}
	int j = 0;
	while (buf[i + j] != '\0')
	{
		if (buf[i + j] != '.')
		{
			buf[i + j] = buf[i + j] + '0';
		}
		res[j] = buf[i + j];
		j++;
	}

}

cal::cal()
{
	res = new unsigned char[200];
	buf = new unsigned char[200];
	memset(buf, 0, 200);
	memset(res, 0, 200);
}
cal::~cal()
{
	delete res;
	delete buf;
	num1 = NULL;
	num2 = NULL;
	res = NULL;
	buf = NULL;
}
cal::cal(const cal &it)
{
	strcpy(this->num1, it.num1);
	strcpy(this->num1, it.num2);
	this->res = new unsigned char[200];
	memset(this->res, 0, 200);
	this->alen1 = it.alen1;
	this->alen2 = it.alen2;
	this->flen1 = it.flen1;
	this->flen2 = it.flen2;
	this->real_len1 = it.real_len1;
	this->real_len2 = it.real_len2;
}
bool cal::init_cal(char* n1, char* n2)
{
	if (strlen(n1) >= 100)
	{
		return 0;
	}
	if (strlen(n2) >= 100)
	{
		return 0;
	}
	if (strstr(n1, "."))
	{
		real_len1 = (int)strstr(n1, ".") - (int)n1;
		flen1 = strlen(n1) - real_len1 - 1;
	}
	else
	{
		real_len1 = strlen(n1);
		flen1 = 0;
	}
	if (strstr(n2, "."))
	{
		real_len2 = (int)strstr(n2, ".") - (int)n2;
		flen2 = strlen(n2) - real_len2 - 1;
	}
	else
	{
		real_len2 = strlen(n2);
		flen2 = 0;
	}
	if (real_len2 > real_len1)
	{
		real_len1 = real_len1 + real_len2;
		real_len2 = real_len1 - real_len2;
		real_len1 = real_len1 - real_len2;
		this->num1 = n2;
		alen1 = strlen(n2);
		this->num2 = n1;
		alen2 = strlen(n1);
		flen1 = flen1 + flen2;
		flen2 = flen1 - flen2;
		flen1 = flen1 - flen2;
	}
	else
	{
		this->num1 = n1;
		alen1 = strlen(n1);
		this->num2 = n2;
		alen2 = strlen(n2);
	}
	return 1;
}
char unsigned* cal::add()
{
	memset(buf, 0, 200);
	for (int i = 0; i < real_len1; i++)
	{
		buf[i + 1] = num1[i] - '0';
	}
	for (int i = 0; i < real_len2; i++)
	{
		buf[real_len1 - i] += (num2[real_len2 - 1 - i] - '0');
	}
	buf[real_len1 + 1] = '.';
	for (int i = 0; i<flen2; i++)
	{
		buf[real_len1 + 2 + i] = num2[real_len2 + 1 + i] - '0';
	}
	for (int i = 0; i<flen1; i++)
	{
		buf[real_len1 + 2 + i] += num1[real_len1 + 1 + i] - '0';
	}
	carry_bit();
	buftores();
	return this->res;
}