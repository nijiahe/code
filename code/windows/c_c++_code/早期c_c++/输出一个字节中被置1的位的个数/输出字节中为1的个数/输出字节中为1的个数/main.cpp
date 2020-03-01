#include<iostream>

using namespace std;
/*实现了输入一个字节,返回这个数的二进制中有几个1*/
int bite1num(char a)
{
	int num = 0;
	unsigned int bite = 1;
	for (int i = 0; i < sizeof(a)*8; i++,bite<<=1)
	{
		if ((a&bite) != 0)
		{
			num++;
		}
	}
	return num;
}
void main()
{
	int num = bite1num(5);
	cout << num << endl;
	cin.get();
}