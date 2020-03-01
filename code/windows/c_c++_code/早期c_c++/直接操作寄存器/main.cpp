#include<iostream>

using namespace std;
void main()
{
	int a = 10;
	int b = 0;
	_asm
	{
		mov eax, a
		add eax, 5
		mov b, eax
	}
	cout << b << endl;

	cin.get();
}