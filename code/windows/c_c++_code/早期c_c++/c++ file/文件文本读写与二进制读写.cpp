#include<iostream>
#include<fstream>
/*put�ǶԶ��������ݵĲ���*/
using namespace std;
/*��*//*�ı��ļ���ȡ*/
/*1.�����ֽڶ�ȡget,put
2.һ��һ�ж�ȡgetline <<*/
/*��*//*�������ļ���ȡ*/
/*1.�����ַ���ȡget put
2.write read, ������Ϊ�׵�ַ,����*/
struct mystruct
{
	char *p = "njh";
	int num1 = 1;
	double num2 = 2.2;
	char ch = 'a';
}mystruct1, mystruct2;
/*c++�����ļ�Ĭ���ı�*/
void main21()
{
	ofstream output("F:\\1.txt",ios::out);
	ifstream input("F:\\1.txt");
	output << mystruct1.p <<" "<< mystruct1.num1 <<" "<< mystruct1.num2 << " " <<mystruct1.ch << endl;
	output.close();
	char str[100] = { 0 };
	input.getline(str, 100);
	cout << str << endl;
	input.close();

	cin.get();
}
/*�����ƶ�д��ʽ*/
/*�Զ����Ʒ�ʽ��д��ʱ��,��д���ļ�ֱ�Ӵ�������,��Ϊֱ�Ӵ��õķ�ʽ���ı���д*/
/*write��д�������,read�Ƕ�ȡ������*/
void main22()
{
	ofstream output("F:\\1.txt", ios::binary);/*�����Ƶķ�ʽд��*/
	mystruct1.p = "asdf";
	output.write((char *)&mystruct1, sizeof(mystruct1));/*�����ַ,����*/
	output.close();
	ifstream input("F:\\1.txt", ios::binary);/*�����Ƶķ�ʽ��ȡ*/
	input.read((char *)&mystruct2, sizeof(mystruct2));
	cout << mystruct2.p << endl;
	cin.get();
}
void main()
{
	ifstream input("F:\\1.txt", ios::binary|ios::in);/*�����Ƶķ�ʽ��ȡ*/
	input.seekg(ios::end);
	size_t size = input.tellg();
	input.seekg(ios::beg);
	input.read((char *)&mystruct2, size);
	cout << mystruct2.p << endl;
	cin.get();
}