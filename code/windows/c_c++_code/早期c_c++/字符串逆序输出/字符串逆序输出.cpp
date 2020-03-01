#include<iostream>
#include<string>

using namespace std;

void reverse(char* str)
{
	int size = strlen(str);
	for (int i = 0; i < size/2; i++)
	{
		char temp=str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = temp;
	}
}

void show(char* str)
{
	int size = strlen(str);
	for (int i = 0; i < size; i++)
	{
		cout << str[i] << " ";
	}
	cout << endl;
}

void main()
{

	char str[] = "123456";
	reverse(str);
	show(str);
	cin.get();
}