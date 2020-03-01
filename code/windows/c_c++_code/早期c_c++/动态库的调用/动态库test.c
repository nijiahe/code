#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

_declspec(dllexport) void message()
{
	MessageBoxA(0, "test", "test", 1);
}