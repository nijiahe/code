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
			_endthread();//结束线程
		}
		printf("run %d秒\n", i);
		Sleep(1000);
		i++;

	}
}

void time(void* ptr)
{
	int i = 0;
	while (1)
	{
		printf("time 第%d个循环",i);
		char str[100] = { 0 };
		sprintf(str, "title 当前时间第%d秒", i);
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
		HANDLE  hd = _beginthread(run, 0, &i);//hd是编号 
		//WaitForSingleObject(hd, INFINITE);//等待,阻塞模式  ，没有wait并行模式
		Sleep(1000);
	}

}