#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef void(*mymessage)();


void main()
{
	HMODULE mydll = LoadLibraryA("MY动态库.dll");//加载动态库"MY动态库.dll";返回一个指针类型,参数类型是动态库的路径
	if (mydll == NULL)
	{
		printf("动态库未找到\n");
	}
	else
	{
		mymessage my1;
		my1 = (mymessage)GetProcAddress(mydll, "message");//在mydll里寻找"message"这个函数,返回值为一个void 类型指针,需要强转
		if (my1 != NULL)
		{
			my1();
		}
		else
		{
			printf("my1==NULL\n");
		}
	
	}
	FreeLibrary(mydll);
	system("pause");
}