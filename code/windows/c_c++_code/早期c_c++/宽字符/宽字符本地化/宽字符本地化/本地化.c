#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<locale.h>

void main()
{
	setlocale(LC_ALL, "chs");//chs和zh-CN一样
	wchar_t ch = L'你';
	wchar_t ptr[] = L"你特码";//宽字符串每一位占两个字节,用L'\0'作为终止符
	wprintf(L"%lc\n", ch);
	wprintf(L"%ls\n", ptr);
	printf("%d\n", *(ptr + 3) == L'\0');
	system("pause");
}
