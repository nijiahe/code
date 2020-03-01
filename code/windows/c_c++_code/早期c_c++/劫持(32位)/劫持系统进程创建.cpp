
//劫持系统注射到exploer(Windows资源管理器)

#include<Windows.h>
#include<stdio.h>
#include"detours.h"
#pragma comment(lib,"detours.lib")

static BOOL(*OLD_CreateProcessW)(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
	) = CreateProcessW;

BOOL MY_CreateProcessW(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
)
{
	MessageBoxW(0, L"进程创建已被劫持", L"信息", 0);
	return 0;
}

void Hook()
{
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((void**)&OLD_CreateProcessW, MY_CreateProcessW);
	DetourTransactionCommit();
}
void UNHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((void**)&OLD_CreateProcessW, MY_CreateProcessW);
	DetourTransactionCommit();
}

_declspec(dllexport)void run()
{
	Hook();
	Sleep(60000);
	UNHook();
}
