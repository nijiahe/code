#pragma once
#include<iostream>
#include "listnode.h"

using namespace std;

template<class T>
class linklist
{
public:
	listnode<T>* ports;//循环接口
	int listlong;//链表元素总数
public:
	linklist();//构造
	~linklist();//析构
	listnode<T>* pushback(T value);//在尾部插入   OK
	listnode<T>* indexinsert(int index,T value);//根据目录数插入  OK
	listnode<T>* revise(int index, T value);//根据目录数修改  OK
	
	listnode<T>* findindex(int index);//根据目录查找   OK
	listnode<T>* findvalue(T value);//根据输入的数据查找		OK
	void merge(linklist<T> anotherlist);//将两个环形链表合并	
	bool remove(int index);//根据目录数删除
	bool remove(listnode<T>* remnode);//根据传入的节点删除
	void listshow();//显示链表所有元素   OK
	//void deletesame();//删除相同的元素
	void rev();//反转链表
	int getlistlong();//返回链表元素数
	void clean();//清理所有元素
};

