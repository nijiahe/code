#include<iostream>
#include<sstream>
#include<string>
using namespace std;
/*put�ǶԶ��������ݵĲ���*/
void main0x()
{
	stringstream mystr("asd");/*��ʼ����ʱ��������ַ���������ַ����ĳ���,���Դӵ�һ����ʼ�滻*/
	mystr.put('X');/*�Ḳ�ǵ�һ���ַ�*/
	mystr.put('X');
	cout << mystr.str();

	
	cin.get();
}

void mainy()
{
	stringstream mystr;/*����һ���ַ�����*/
	char cmd1[30] = { 0 };
	char cmd2[30] = { 0 };
	cin.getline(cmd1, 30).getline(cmd2, 30);
	mystr << cmd1 << '&' << cmd2;/*���Ӽ��̻�ȡ��line���뵽mystr��*/
	cout << mystr.str()<<endl;/*�����calc&calc*/
	system(mystr.str().c_str());/*mystr.str()���ص���һ��c++���͵��ַ���string,Ҫ����ת����c���Է���*/
	
	char tempstr[50] = { 0 };
	strcpy_s(tempstr, mystr.str().c_str());/*��mystr����ַ���ת��Ϊc���strcpy��char������*/
	for (char* p = tempstr; *p != '\0'; p++)
	{
		if (*p == '&')
		{
			*p = ' ';
		}
	}
	char newcmd1[26] = { 0 };
	char newcmd2[26] = { 0 };
	stringstream newstr(tempstr);/*����һ������tempstr��ʼ��,��ʱtempstr����calc calc*/
	newstr >> newcmd1 >> newcmd2;
	cout << newcmd1 << '\n' << newcmd2;
	

	cin.get();
	cin.get();
}