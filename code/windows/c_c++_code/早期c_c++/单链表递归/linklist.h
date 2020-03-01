#ifndef LINKLIST_H
#define LINKLIST_H
//һ������ṹ�洢ͷ�ڵ��β�ڵ�
#include<iostream>
#include"listnode.h"


using namespace std;
template<class T> class listnode;//������
template<class T> void run(linklist<T> &it);//������Ԫ����
											/*����ģ����ʹ����Ԫ��������Ҫ���ඨ��ǰ���Ϻ���������*/

template<class T>
class linklist
{
private:
	listnode<T>* topnode;
	listnode<T>* tailnode;
public:
	linklist();
	~linklist();
public:
	void ListInsertHead(T value);//ǰ��  OK
	void ListInsertTail(T value);//β��  OK
	void ListInsertIndex(int index, T value);//����Ŀ¼������Ŀ¼������һ���ڵ����ڵ�   OK
	void ListSort(bool flag);//�������������   OK
	void ListShow();//��������,��ʾ���нڵ�     OK
	listnode<T> * ListFindIndex(int index);//����Ŀ¼�����ص�index���ڵ�ĵ�ַ    OK
	listnode<T> * ListFindValue(T value);//���ҵ�һ������ָ��ֵ�Ľڵ�ĵ�ַ   OK
	/*��ʵ����Ϊintʱ��������Ǹ������ظ�����,����ȥ��*///void ListRemove(int index);//����Ŀ¼��ɾ���ڵ�    OK
	void ListRemove(T value);//����ֵɾ���ڵ�      OK
	void ListRemove(listnode<T>* valuenode);//���ݽڵ��ַɾ���ڵ�   OK
											/*?���ʵ��void ListRemove(int index��Args...args)?*/
	void ListRevise(int index, T value);//����Ŀ¼���޸ĸ�Ŀ¼�ڵ������  OK
	friend void run<T>(linklist<T> &it);//��ģ����Ԫ��������*/
										/*�������ֻ����T�����µ���Ԫ����������ͨ��������͵ĺ������ʱ�����͵���*/
	T Maxkey(int n);//�ݹ�ʵ�ַ���ǰn�����е����ֵ     OK
	int nodecount(listnode<T>* node);//�ݹ�ʵϰ������Ľ�����      OK
	double Average(int n);//�ݹ�ʵ����n������ƽ��ֵ     OK
};


#endif // LINKLIST_H
