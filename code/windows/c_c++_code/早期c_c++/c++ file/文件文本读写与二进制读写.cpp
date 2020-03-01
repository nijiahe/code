#include<iostream>
#include<fstream>
/*put是对二进制数据的操作*/
using namespace std;
/*①*//*文本文件读取*/
/*1.单个字节读取get,put
2.一行一行读取getline <<*/
/*②*//*二进制文件读取*/
/*1.单个字符读取get put
2.write read, 参数均为首地址,长度*/
struct mystruct
{
	char *p = "njh";
	int num1 = 1;
	double num2 = 2.2;
	char ch = 'a';
}mystruct1, mystruct2;
/*c++处理文件默认文本*/
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
/*二进制读写方式*/
/*以二进制方式读写的时候,读写的文件直接打开是乱码,因为直接打开用的方式是文本读写*/
/*write是写入二进制,read是读取二进制*/
void main22()
{
	ofstream output("F:\\1.txt", ios::binary);/*二进制的方式写入*/
	mystruct1.p = "asdf";
	output.write((char *)&mystruct1, sizeof(mystruct1));/*传入地址,长度*/
	output.close();
	ifstream input("F:\\1.txt", ios::binary);/*二进制的方式读取*/
	input.read((char *)&mystruct2, sizeof(mystruct2));
	cout << mystruct2.p << endl;
	cin.get();
}
void main()
{
	ifstream input("F:\\1.txt", ios::binary|ios::in);/*二进制的方式读取*/
	input.seekg(ios::end);
	size_t size = input.tellg();
	input.seekg(ios::beg);
	input.read((char *)&mystruct2, size);
	cout << mystruct2.p << endl;
	cin.get();
}