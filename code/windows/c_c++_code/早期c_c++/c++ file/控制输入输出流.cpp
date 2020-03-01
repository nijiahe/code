#include<iostream>
#include<iomanip>/*控制输入输出流头文件*/
using namespace std;

void main01()
{

	cout.put('A').put('b')<<endl;/*输出单个字节*/
	char str[] = "1235678946312aaaa";
	cout.write(str, 10);/*输出字符串*/
	cin.get();
}
/*设置进制*/
void main02()
{
	int num = 10;
	cout << num << endl;/*默认十进制*/
	cout << hex;/*十六进制*/
	cout << num << endl;
	cout << oct;/*八进制*/
	cout << num << endl;
	cout << dec;/*十进制*/
	cout << num;

	cin.get();
}
/*设置有效位数*/
void main03()
{
	double db = 1243.21212121212;/*默认保留6位有效数字*/
	/*cout << setprecision(15);/*设置最多保存几位有效数字*/
	cout << db << endl;
	cin.get();
}
/*设置填充*/
void main04()
{
	cout.width(10);/*设置总宽度40*/
	/*填充的样式*/
	cout.fill('*');
	/*设置的下一次输出时的样式*/
	cout << "hello";
	cout.setf(ios::right);/*输出内容右对齐*/
	cout.width(5);
	cout.fill('*');
	cout << " ";
	
	cout.fill('*');
	cin.get();

}
void main05()
{
	int a;
	cin.setf(ios::hex, ios::basefield);/*设置cin传入的形式(设置进制,修改传入进制)*/
	cin >> a;
	cout << oct;/*设置下一次输出样式八进制*/
	cout << a;
	cin.get();
	cin.get();
}
void main06()
{
	double db = 1000 / 7.0;/*double默认保留6个小数位数*/
	cout.setf(ios::fixed | ios::showpoint);/*设置小数点,显示小数点*/
	for (int i = 0; i <10 ; i++)
	{
		cout.precision(i);/*设置小数点位数*/
		cout << db << endl;
	}
	cout << db << endl;
	cout.setf(ios::scientific,ios::fixed | ios::showpoint);/*用科学记数法*/
	/*自动选择小数或指数*/
	cout << db << endl;
	cin.get();
	cin.get();
}

void main07()
{
	const int num = 1234;
	cout << setw(10) << setfill('*') << setiosflags(ios::left) << num<<endl;
	cout << setw(10) << setfill('*') << setiosflags(ios::right) << num<<endl;
	cout << resetiosflags(ios::right)<<setw(10) << setbase(8) << setfill('*') << setiosflags(ios::left) << num << endl;
	/*显示器<<清除历史操作并设置为右对齐<<设置总宽度10<<设置输出进制8<<输出填充字符'*'<<设置左对齐<<输出num<<*/
	cin.get();
	cin.get();
}