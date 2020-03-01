#include<iostream>
#include<sstream>/*字符串输入输出,第一个s代表string*/
#include<string>

using namespace std;

struct Mystruct
{
	string str1, str2, str3;
	double db;
	int num;
	char ch;
};

/*用字符串作分割*/
void main0a()
{
	string mystring("a1 b2 c3 4.4 5 a");
	Mystruct struct1;
	istringstream input(mystring);/*创建一个字符串扫描流input*/
	input >> struct1.str1 >> struct1.str2 >> struct1.str3 >> struct1.db >> struct1.num >> struct1.ch;/*提取扫描到struct1里*/
	/*输出扫描结果*/
	cout << struct1.str1<<endl;
	cout << struct1.str2 << endl;
	cout << struct1.str3 << endl;
	cout << struct1.db << endl;
	cout << struct1.num << endl;
	cout << struct1.ch << endl;
	cin.get();
}
/*用#做分割*/
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
	istringstream input(mystring);/*创建一个输入流,用mystring初始化,输入流会自动扫描这个字符串*/
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