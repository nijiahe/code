#include <iostream>
#include"linklist.h"
/*ģ���಻��һ�����ͣ�ʵ����ģ�����ʱ����Ҫ�������еĺ�����������Ϊֻ֪����������֪�����壬û�а취ʵ������
* ���Ҫʵ��������Ҫ��ģ�����е�ͷ�ļ��о���ɶ�ģ����Ķ��壬������main.cpp�а�������ģ���ļ��Ķ���*/
#include"linklist.cpp"
using namespace std;

void main()
{
	linklist<int> list1;
	list1.ListInsertHead(1);
	list1.ListInsertHead(2);
	list1.ListInsertHead(3);
	list1.ListInsertHead(4);
	list1.ListInsertHead(5);
	list1.ListInsertHead(6);
	list1.ListInsertHead(7);
	list1.ListInsertHead(8);
	list1.ListInsertHead(9);
	list1.ListShow();
	cout << list1.Maxkey(list1.nodecount(list1.ListFindIndex(1))) << endl;//���ֵ
	cout << list1.nodecount(list1.ListFindIndex(1)) << endl;//�ڵ���
	cout << list1.Average(list1.nodecount(list1.ListFindIndex(1))) << endl;//ƽ��ֵ


	cin.get();
}