#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>


//用unicode解析就需要加上L"",可以更好的表示中文
//用多字节字符集解析不用加什么,但可能出错

void mainA()
{
	MessageBox(0, L"倪嘉禾", L"倪嘉禾", 0);//使用当前的字符集来解析,用unicode解析需要加上L"",多字节字符集可以
	//加上L是表明用多字符集解析
	MessageBoxA(0, "倪嘉禾", "倪嘉禾", 0);
	//MessageBoxA用多字符集解析
	MessageBoxW(0, L"倪嘉禾", L"倪嘉禾", 0);
	//MessageBoxW用unicode字符集解析
	MessageBox(0, TEXT("倪嘉禾"), TEXT("倪嘉禾"), 0);
	//如果定义了UNICODE,TEXT作用就相当于L,否则就按照多字节字符集解析
}