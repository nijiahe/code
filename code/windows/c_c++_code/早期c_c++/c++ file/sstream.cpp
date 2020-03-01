#include<iostream>
#include<sstream>
#include<string>
using namespace std;
/*put是对二进制数据的操作*/
void main0x()
{
	stringstream mystr("asd");/*初始化的时候输入的字符不会计入字符串的长度,所以从第一个开始替换*/
	mystr.put('X');/*会覆盖第一个字符*/
	mystr.put('X');
	cout << mystr.str();

	
	cin.get();
}

void mainy()
{
	stringstream mystr;/*创建一个字符串流*/
	char cmd1[30] = { 0 };
	char cmd2[30] = { 0 };
	cin.getline(cmd1, 30).getline(cmd2, 30);
	mystr << cmd1 << '&' << cmd2;/*将从键盘获取的line输入到mystr中*/
	cout << mystr.str()<<endl;/*输出了calc&calc*/
	system(mystr.str().c_str());/*mystr.str()返回的是一个c++类型的字符串string,要把它转化成c语言风格的*/
	
	char tempstr[50] = { 0 };
	strcpy_s(tempstr, mystr.str().c_str());/*将mystr里的字符串转化为c风格并strcpy到char数组里*/
	for (char* p = tempstr; *p != '\0'; p++)
	{
		if (*p == '&')
		{
			*p = ' ';
		}
	}
	char newcmd1[26] = { 0 };
	char newcmd2[26] = { 0 };
	stringstream newstr(tempstr);/*创建一个流用tempstr初始化,此时tempstr中是calc calc*/
	newstr >> newcmd1 >> newcmd2;
	cout << newcmd1 << '\n' << newcmd2;
	

	cin.get();
	cin.get();
}