#include<iostream>
#include<sstream>/*�ַ����������,��һ��s����string*/
#include<string>

using namespace std;

struct Mystruct
{
	string str1, str2, str3;
	double db;
	int num;
	char ch;
};

/*���ַ������ָ�*/
void main0a()
{
	string mystring("a1 b2 c3 4.4 5 a");
	Mystruct struct1;
	istringstream input(mystring);/*����һ���ַ���ɨ����input*/
	input >> struct1.str1 >> struct1.str2 >> struct1.str3 >> struct1.db >> struct1.num >> struct1.ch;/*��ȡɨ�赽struct1��*/
	/*���ɨ����*/
	cout << struct1.str1<<endl;
	cout << struct1.str2 << endl;
	cout << struct1.str3 << endl;
	cout << struct1.db << endl;
	cout << struct1.num << endl;
	cout << struct1.ch << endl;
	cin.get();
}
/*��#���ָ�*/
void main0b()
{
	char mystring[50] = "china#123#A";
	/*mystring.replace('#', " ");*/
	for (char *p = mystring; *p != '\0'; p++)
	{
		if (*p == '#')
		{
			*p = ' ';
		}
	}
	string str;
	int num;
	char ch;
	istringstream input(mystring);/*����һ��������,��mystring��ʼ��,���������Զ�ɨ������ַ���*/
	input >> str >> num >> ch;
	cout << str << endl;
	cout << num << endl;
	cout << ch << endl;
	cin.get();
}

void main0c()
{
	ostringstream output;
	string mystr("hahaah123");
	output << mystr <<"enen"<< endl;
	cout << output.str();
	cin.get();
}