#include<iostream>
#include<fstream>

using namespace std;
/*��*//*�ļ�д��*//*ofstream*/
void mainone()
{	
	/*����һ���ļ����������ָ��,����FILE* pf*/
	/*fstream fout;/*fstream����ֻ�޸Ĳ���*/
	/*ofstream fout("F:\\1.txt");/*ofstream������ȫ����*/
	/*Ϊ���ָ��ָ��һ���ļ�,����*/
	//fout.open("F:\\1.txt");
	ofstream fout("F:\\1.txt", ios::out);/*�����ļ�,ָ���򿪷�ʽ*/
	fout << "123";
	fout.close();
	cout << "F:\\1.txt";
	cin.get();
}
/*��*//*�ļ���ȡ*//*ifstream*/
void maintwo()
{
	ifstream fin("F:\\1.txt");
	char str[50];
	fin >> str;
	cout << str;
	fin.close();
	cin.get();
}
/*��*//*�ļ���ȡһ��*/
/*getline*/
void mainthree()
{
	ifstream fin("F:\\1.txt");
	char str[50] = { 0 };
	for (int i = 0; fin.getline(str, 50); i++)
	{			
		cout << str << endl;
	}
	fin.close();
	cin.get();
}
/*��*//*���ļ�����*/
void mainfour()
{
	/*������*/
	ifstream input1;
	input1.open("F:\\1.txt", ios::in);
	/*���������ļ���,�����ļ�,ָ���򿪷�ʽ*/
	ofstream output1;
	output1.open("F:\\1.txt", ios::out);
	/*��������ļ���,�����ļ�,�ƶ��򿪷�ʽ*/

	/*������*//*�����ļ������������캯��*/
	ifstream infile("F:\\1.txt", ios::in);
	ofstream outfile("F:\\1.txt", ios::out);
	fstream rwfile("F:\\1.txt", ios::in | ios::out);
}
/*��*//*fstream*//*�ļ�����ȡ��д��*/
void mainfive()
{
	fstream rwfile1("F:\\1.txt", ios::in | ios::out);/*����һ��fstream�ļ���ָ��,ʵ�ֶ�ȡ��д��*/
	int num;
	char str[50];
	char ch;
	rwfile1 >> num >> str >> ch;/*��ȡ�ļ�����Ϣ*/
	cout << num << endl;
	cout << str << endl;
	cout << ch << endl;
	rwfile1.close();
	fstream rwfile2("F:\\2.txt",ios::out|ios::in);
	rwfile2 << num << " " << str << " " << ch << endl;/*���ļ���������Ϣ*/
	
	cin.get();
}
/*��*//*�ļ�׷��*/
void mainsix()
{
	ofstream fadd("F:\\1.txt", ios::app);
	if (!fadd)
	{
		cout << "ʧ��" << endl;
		cin.get();
		return;
	}
	fadd << "add test";
	fadd.close();


	cin.get();
}