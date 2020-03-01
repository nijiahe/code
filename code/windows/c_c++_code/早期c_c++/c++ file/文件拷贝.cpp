#include<iostream>
#include<fstream>/*文件流指针头文件*/
/*从F:\\3.txt拷贝到F:\\1.txt*/
using namespace std;

void maincopy()
{
	ifstream input("F:\\3.txt", ios::in);
	ofstream output("F:\\1.txt", ios::out);
	if (!input || !output)/*如果input不是一个文件指针或者output不是一个文件指针*/
	{
		cout << "文件指针创建失败" << endl;
		cin.get();
		return;
	}
	cout << "开始拷贝" << endl;
	char ch;
	while (input.get(ch))/*当input读取到char时*/
	{
		output.put(ch);/*输出ch到output打开的文件*/
	}
	cout << "拷贝完成" << endl;
	input.close();
	output.close();

	cin.get();
}