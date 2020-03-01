#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

#include"detours.h"
#pragma comment(lib, "detours.lib")

//劫持自己

static int (*poldsystem)( const char * _Command)=system;//存储函数指针地址

int  newsystem(const char * _Command)
{

	//tasklist

	printf("%s", _Command); //禁止你干活
	
	return 0;
}
int  newsystemA(const char * _Command)
{

	//tasklist   过滤
	char *p = strstr(_Command, "tasklist");
	if (p == NULL)
	{
		
		poldsystem(_Command);
	}
	else
	{
		printf("%s禁止执行", _Command);//找到
		return 0;
	}

	

	return 0;
}

//开始拦截
void Hook()
{


	DetourRestoreAfterWith();//恢复原来状态
	DetourTransactionBegin();//拦截开始
	DetourUpdateThread(GetCurrentThread());//刷新当前线程
	//这里可以连续多次调用DetourAttach，表明HOOK多个函数
	DetourAttach((void **)&poldsystem, newsystemA);//实现函数拦截
	DetourTransactionCommit();//拦截生效


}
void main()
{

	system("calc");
	Hook();
	system("calc");
	system("tasklist");
	getchar();

}