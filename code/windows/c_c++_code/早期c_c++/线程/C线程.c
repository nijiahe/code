#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>


void run(void* ptr)
{
	int i = 0;
	while (1)
	{
		if (i > 5)
		{
			_endthread();//�����߳�
		}
		printf("run %d��\n", i);
		Sleep(1000);
		i++;

	}
}

void time(void* ptr)
{
	int i = 0;
	while (1)
	{
		printf("time ��%d��ѭ��",i);
		char str[100] = { 0 };
		sprintf(str, "title ��ǰʱ���%d��", i);
		system(str);
		i++;
		Sleep(1000);
	}
}

int main()
{
	_beginthread(time, 0, NULL);
	for (int i = 0; i < 5; i++)
	{
		HANDLE  hd = _beginthread(run, 0, &i);//hd�Ǳ�� 
		//WaitForSingleObject(hd, INFINITE);//�ȴ�,����ģʽ  ��û��wait����ģʽ
		Sleep(1000);
	}

}