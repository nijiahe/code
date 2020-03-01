#define _CRT_SECURE_NO_WARNINGS
#ifndef __BIGDATA_CALCULATE_H_
#define __BIGDATA_CALCULATE_H_
#include<iostream>
class cal
{
public:
	char* num1;
	char* num2;
	char unsigned * res;
	char unsigned * buf;
	int real_len1;
	int real_len2;
	int alen1;
	int alen2;
	int flen1;
	int flen2;
	void carry_bit();
	void buftores();
public:
	cal();
	~cal();
	cal(const cal &it);
	bool init_cal(char* num1, char* num2);
	char unsigned * add();

};
#endif
