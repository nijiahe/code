#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>


//��unicode��������Ҫ����L"",���Ը��õı�ʾ����
//�ö��ֽ��ַ����������ü�ʲô,�����ܳ���

void mainA()
{
	MessageBox(0, L"�߼κ�", L"�߼κ�", 0);//ʹ�õ�ǰ���ַ���������,��unicode������Ҫ����L"",���ֽ��ַ�������
	//����L�Ǳ����ö��ַ�������
	MessageBoxA(0, "�߼κ�", "�߼κ�", 0);
	//MessageBoxA�ö��ַ�������
	MessageBoxW(0, L"�߼κ�", L"�߼κ�", 0);
	//MessageBoxW��unicode�ַ�������
	MessageBox(0, TEXT("�߼κ�"), TEXT("�߼κ�"), 0);
	//���������UNICODE,TEXT���þ��൱��L,����Ͱ��ն��ֽ��ַ�������
}