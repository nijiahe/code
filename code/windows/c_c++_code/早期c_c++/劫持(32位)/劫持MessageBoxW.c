
//劫持要在Release才生效

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>//存在了一些detours.h里需要的数据类型


#include"detours.h"
#pragma comment(lib, "detours.lib")


//自己定义的新MessageBoxW
int (WINAPI MY_MessageBoxW)(HWND a, LPCWSTR b, LPCWSTR c, UINT d)
{
	printf("已劫持\n");
	return 1;
}
//定义函数指针指向MessageBoxW
static int (WINAPI* OLD_MessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT) = MessageBoxW;


//开始劫持
void HOOK()
{
	DetourRestoreAfterWith();//恢复原来状态
	DetourTransactionBegin();//拦截开始
	DetourUpdateThread(GetCurrentThread());//刷新当前进程
	//可以多次调用DetourAttach来表示劫持多个函数
	DetourAttach((void **)&OLD_MessageBoxW, MY_MessageBoxW);//劫持
	DetourTransactionCommit();//劫持生效
}

//取消劫持
void UNHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((void **)&OLD_MessageBoxW, MY_MessageBoxW);
	DetourTransactionCommit();
}

void main()
{
	MessageBoxW(0, L"第1个", L"1", 0);
	HOOK();
	MessageBoxW(0, L"第2个", L"2", 0);
	UNHook();
	MessageBoxW(0, L"第3个", L"3", 0);
	system("pause");
}