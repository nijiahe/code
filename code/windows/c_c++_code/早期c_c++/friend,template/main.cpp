#include <iostream>
#include"linklist.h"
/*ģ���಻��һ�����ͣ�ʵ����ģ�����ʱ����Ҫ�������еĺ�����������Ϊֻ֪����������֪�����壬û�а취ʵ������
* ���Ҫʵ��������Ҫ��ģ�����е�ͷ�ļ��о���ɶ�ģ����Ķ��壬������main.cpp�а�������ģ���ļ��Ķ���*/
#include"linklist.cpp"
using namespace std;

int main()
{

	linklist<double> list1;
	list1.ListInsertHead(1.1);
	list1.ListInsertHead(2.1);
	list1.ListInsertHead(3.1);
	list1.ListInsertHead(4.1);
	list1.ListInsertTail(5.1);
	list1.ListInsertIndex(3, 10.1);
	list1.ListInsertIndex(1, 8.1);
	list1.ListSort(1);
	list1.ListShow();
	std::cout << "**********************" << std::endl;
	list1.ListRemove(1.1);
	list1.ListShow();
	run(list1);//��ģ����Ԫ��������
	/*test<double> test1;
	test1.show(list1);//��ģ����Ԫ�����*/
	

	std::cin.get();
	return 0;
}