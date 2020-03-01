#include<iostream>
#include<fstream>

using namespace std;
/*①*//*读取*//*读取用seekg*/
void main31()
{
	ofstream fout("F:\\1.txt", ios::out);
	fout << "1234567890abcdefg";
	fout.close();
	ifstream fin("F:\\1.txt");
	char str[50];
	/*将光标移到开头往后的9个字节的地方,get和getline都会从光标之后开始获取*/
	/*fin.seekg(9, ios::beg);
	fin.get(str, 50);
	cout << str << endl;*/
	/*将光标移到结尾往前的9个字节的地方,get和getline都会从光标之后开始获取*/
	fin.seekg(-9, ios::end);
	fin.get(str, 50);
	cout << str << endl;
	/*将光标移动到当前位置往往前9个字节,如果到达文件头或末尾会停止*/
	fin.seekg(-3, ios::cur);
	fin.get(str, 50);
	cout << str << endl;
	cin.get();
}
/*②*//*写入*//*写入时用seekp*/
void main32()
{
	/*只读,全覆盖一行*/
	ofstream fout1("F:\\1.txt", ios::out);
	fout1 << "11112222333344445555";
	fout1.close();
	/*读写,覆盖被修改处*/
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
/*ofstream fout("F:\\3.txt", ios::out);如果这样创建,只能写入,不能读取里面有几个字符*/
void main33()
{
	ofstream fout("F:\\3.txt", ios::out|ios::in);
	fout.seekp(0,ios::end);
	int size = fout.tellp();
	cout << size << endl;/*返回当前指针到ios::begin的距离*/
	fout.close();
	cin.get();

}
