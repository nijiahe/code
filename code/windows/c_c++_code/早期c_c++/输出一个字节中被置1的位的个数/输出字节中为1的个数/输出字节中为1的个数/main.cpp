#include<iostream>

using namespace std;
/*ʵ��������һ���ֽ�,����������Ķ��������м���1*/
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