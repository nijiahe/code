#include<Windows.h>
#include<stdio.h>
#include<string.h>

#include"detours.h"
#pragma comment(lib,"detours.lib")

static int (*Oldsystem)(char const* _Command);
int MYsystem(char const* _Command)
{
	return 0;
}

void Hook()
{
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((void**)&Oldsystem, MYsystem);
	DetourTransactionCommit();
}

_declspec(dllexport) void go()
{
	MessageBoxA(0, "1", "2", 0);
	Hook();
}