#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

#include"detours.h"
#pragma comment(lib, "detours.lib")

//�ٳ��Լ�

static int (*poldsystem)( const char * _Command)=system;//�洢����ָ���ַ

int  newsystem(const char * _Command)
{

	//tasklist

	printf("%s", _Command); //��ֹ��ɻ�
	
	return 0;
}
int  newsystemA(const char * _Command)
{

	//tasklist   ����
	char *p = strstr(_Command, "tasklist");
	if (p == NULL)
	{
		
		poldsystem(_Command);
	}
	else
	{
		printf("%s��ִֹ��", _Command);//�ҵ�
		return 0;
	}

	

	return 0;
}

//��ʼ����
void Hook()
{


	DetourRestoreAfterWith();//�ָ�ԭ��״̬
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
	//�������������ε���DetourAttach������HOOK�������
	DetourAttach((void **)&poldsystem, newsystemA);//ʵ�ֺ�������
	DetourTransactionCommit();//������Ч


}
void main()
{

	system("calc");
	Hook();
	system("calc");
	system("tasklist");
	getchar();

}