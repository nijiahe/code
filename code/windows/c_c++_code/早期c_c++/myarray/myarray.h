#ifndef MYARRAY_H
#define MYARRAY_H

#include<string>
#include<iostream>

template<class T, int N>
class myarray
{
public:
	T *dataptr;
public:
	myarray();//���캯��
	~myarray();//��������
	T operator [](int index);//����[]
	myarray(const myarray<T, N>& it);//��������	
	void init(int value, T...);//���������ʼ�����޸�
	void showmyarray();//չʾ������������
	T revise(int index,int value);//�������Ŀ¼�޸ĵ���Ԫ��
};

#endif // MYARRAY_H
