#include<iostream>
#include<set>
#include<string>

using namespace std;

struct strless
{
	bool operator()(const char *str1,const char* str2) const
	{/*��str1<str2���ظ�ֵ,��str1=str2����0,��str1>str2��������,�Ƚϴ�С���ֵ����򷽷�һ��*/
		return strcmp(str1, str2)<0 ;
	}
};


void main60()
{/*Ԫ������,���򷽷�*/
	set<char*, strless>myset1;
	myset1.insert("zzt");
	myset1.insert("ly");
	myset1.insert("njh");
	for (auto ibegin = myset1.begin(); ibegin != myset1.end(); ibegin++)
	{
		cout << *ibegin << endl;
	}
	cin.get();
}

void main61()
{
	const char* cmd[] = { "abc","calc","ly","njh","zzt" };
	set<const char*, strless>myset1(cmd, cmd + 5, strless());
	for (auto ibegin = myset1.begin(); ibegin != myset1.end(); ibegin++)
	{
		cout << *ibegin << endl;
	}
	/*�����ַ���insert��ʱ�򷵻�һ��pair����,�������Լ�������pairģ������ʵ��������*/
	//pair<set<const char*>::iterator, bool>p=myset1.insert("9876");
	auto p = myset1.insert("9876");
	/*p.first����һ��conditional����,������*,*p���insert��ֵ,p.second���ص���boolֵ*/
	cout << *(p.first) << " " << p.second << endl;
	/*set<const char *, strless>::iterator pfind = myset1.find("abc");
	cout << "\n\n\n" << *pfind << endl;*/
	cin.get();
} 