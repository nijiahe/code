#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef void(*mymessage)();


void main()
{
	HMODULE mydll = LoadLibraryA("MY��̬��.dll");//���ض�̬��"MY��̬��.dll";����һ��ָ������,���������Ƕ�̬���·��
	if (mydll == NULL)
	{
		printf("��̬��δ�ҵ�\n");
	}
	else
	{
		mymessage my1;
		my1 = (mymessage)GetProcAddress(mydll, "message");//��mydll��Ѱ��"message"�������,����ֵΪһ��void ����ָ��,��Ҫǿת
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