#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<locale.h>

void main()
{
	setlocale(LC_ALL, "chs");//chs��zh-CNһ��
	wchar_t ch = L'��';
	wchar_t ptr[] = L"������";//���ַ���ÿһλռ�����ֽ�,��L'\0'��Ϊ��ֹ��
	wprintf(L"%lc\n", ch);
	wprintf(L"%ls\n", ptr);
	printf("%d\n", *(ptr + 3) == L'\0');
	system("pause");
}
