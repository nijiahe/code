#include<iostream>
#include<fstream>

using namespace std;
/*��*//*��ȡ*//*��ȡ��seekg*/
void main31()
{
	ofstream fout("F:\\1.txt", ios::out);
	fout << "1234567890abcdefg";
	fout.close();
	ifstream fin("F:\\1.txt");
	char str[50];
	/*������Ƶ���ͷ�����9���ֽڵĵط�,get��getline����ӹ��֮��ʼ��ȡ*/
	/*fin.seekg(9, ios::beg);
	fin.get(str, 50);
	cout << str << endl;*/
	/*������Ƶ���β��ǰ��9���ֽڵĵط�,get��getline����ӹ��֮��ʼ��ȡ*/
	fin.seekg(-9, ios::end);
	fin.get(str, 50);
	cout << str << endl;
	/*������ƶ�����ǰλ������ǰ9���ֽ�,��������ļ�ͷ��ĩβ��ֹͣ*/
	fin.seekg(-3, ios::cur);
	fin.get(str, 50);
	cout << str << endl;
	cin.get();
}
/*��*//*д��*//*д��ʱ��seekp*/
void main32()
{
	/*ֻ��,ȫ����һ��*/
	ofstream fout1("F:\\1.txt", ios::out);
	fout1 << "11112222333344445555";
	fout1.close();
	/*��д,���Ǳ��޸Ĵ�*/
	ofstream fout2("F:\\1.txt", ios::out|ios::in);
	fout2.seekp(7, ios::beg);
	char str[] = "asdfg";
	fout2 << str;
	fout2.close();

	ifstream fin("F:\\1.txt");
	char str2[50] = { 0 };
	fin >> str2;
	cout << str2<< endl;
	cin.get();
}
/*ofstream fout("F:\\3.txt", ios::out);�����������,ֻ��д��,���ܶ�ȡ�����м����ַ�*/
void main33()
{
	ofstream fout("F:\\3.txt", ios::out|ios::in);
	fout.seekp(0,ios::end);
	int size = fout.tellp();
	cout << size << endl;/*���ص�ǰָ�뵽ios::begin�ľ���*/
	fout.close();
	cin.get();

}
