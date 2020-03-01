
//�ٳ�Ҫ��Release����Ч

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>//������һЩdetours.h����Ҫ����������


#include"detours.h"
#pragma comment(lib, "detours.lib")


//�Լ��������MessageBoxW
int (WINAPI MY_MessageBoxW)(HWND a, LPCWSTR b, LPCWSTR c, UINT d)
{
	printf("�ѽٳ�\n");
	return 1;
}
//���庯��ָ��ָ��MessageBoxW
static int (WINAPI* OLD_MessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT) = MessageBoxW;


//��ʼ�ٳ�
void HOOK()
{
	DetourRestoreAfterWith();//�ָ�ԭ��״̬
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ����
	//���Զ�ε���DetourAttach����ʾ�ٳֶ������
	DetourAttach((void **)&OLD_MessageBoxW, MY_MessageBoxW);//�ٳ�
	DetourTransactionCommit();//�ٳ���Ч
}

//ȡ���ٳ�
void UNHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((void **)&OLD_MessageBoxW, MY_MessageBoxW);
	DetourTransactionCommit();
}

void main()
{
	MessageBoxW(0, L"��1��", L"1", 0);
	HOOK();
	MessageBoxW(0, L"��2��", L"2", 0);
	UNHook();
	MessageBoxW(0, L"��3��", L"3", 0);
	system("pause");
}