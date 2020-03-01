#include<iostream>
#include<fstream>

using namespace std;
/*①*//*文件写入*//*ofstream*/
void mainone()
{	
	/*创建一个文件输入输出流指针,类似FILE* pf*/
	/*fstream fout;/*fstream代表只修改部分*/
	/*ofstream fout("F:\\1.txt");/*ofstream代表完全覆盖*/
	/*为这个指针指定一个文件,并打开*/
	//fout.open("F:\\1.txt");
	ofstream fout("F:\\1.txt", ios::out);/*连接文件,指定打开方式*/
	fout << "123";
	fout.close();
	cout << "F:\\1.txt";
	cin.get();
}
/*②*//*文件读取*//*ifstream*/
void maintwo()
{
	ifstream fin("F:\\1.txt");
	char str[50];
	fin >> str;
	cout << str;
	fin.close();
	cin.get();
}
/*③*//*文件读取一行*/
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
/*④*//*打开文件方法*/
void mainfour()
{
	/*方法①*/
	ifstream input1;
	input1.open("F:\\1.txt", ios::in);
	/*建立输入文件流,连接文件,指定打开方式*/
	ofstream output1;
	output1.open("F:\\1.txt", ios::out);
	/*建立输出文件流,连接文件,制定打开方式*/

	/*方法②*//*调用文件流带参数构造函数*/
	ifstream infile("F:\\1.txt", ios::in);
	ofstream outfile("F:\\1.txt", ios::out);
	fstream rwfile("F:\\1.txt", ios::in | ios::out);
}
/*⑤*//*fstream*//*文件简单提取与写入*/
void mainfive()
{
	fstream rwfile1("F:\\1.txt", ios::in | ios::out);/*创建一个fstream文件流指针,实现读取和写入*/
	int num;
	char str[50];
	char ch;
	rwfile1 >> num >> str >> ch;/*提取文件中信息*/
	cout << num << endl;
	cout << str << endl;
	cout << ch << endl;
	rwfile1.close();
	fstream rwfile2("F:\\2.txt",ios::out|ios::in);
	rwfile2 << num << " " << str << " " << ch << endl;/*向文件中输入信息*/
	
	cin.get();
}
/*⑥*//*文件追加*/
void mainsix()
{
	ofstream fadd("F:\\1.txt", ios::app);
	if (!fadd)
	{
		cout << "失败" << endl;
		cin.get();
		return;
	}
	fadd << "add test";
	fadd.close();


	cin.get();
}