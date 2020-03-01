#include<Windows.h>
#include<stdio.h>
#include<string.h>

#include"detours.h"
#pragma comment(lib,"detours.lib")

static int( *OLDsystem)(char const* _Command) = system;

int  MYsystem(char const* _Command)
{
	if (strcmp(_Command, "calc") == 0)
	{
		printf("ря╫ыЁж\n");
	}
	else
	{
		OLDsystem(_Command);
	}
	return 1;
}

void Hook()
{
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((void**)&OLDsystem, MYsystem);
	DetourTransactionCommit();
}
int main()
{
	Hook();
	system("calc");
	system("pause");
	return 1;
}