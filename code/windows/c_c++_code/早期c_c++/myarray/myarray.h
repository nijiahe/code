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
	myarray();//构造函数
	~myarray();//析构函数
	T operator [](int index);//重载[]
	myarray(const myarray<T, N>& it);//拷贝构造	
	void init(int value, T...);//数组整体初始化、修改
	void showmyarray();//展示数组所有数据
	T revise(int index,int value);//数组根据目录修改单个元素
};

#endif // MYARRAY_H
