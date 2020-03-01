#include<iostream>
#include<stdlib.h>

using namespace std;
/*get一旦接收到设定的结束字符就不再接收*/

void main11()
{
	char buf[80];
	cin.get(buf, 80);
	cout << buf << '\n';
	cin.get(buf, 80);
	cout << buf << '\n';
	cin.get(buf, 80);
	cout << buf << '\n';
	system("pause");
}