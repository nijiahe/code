#pragma once
#include<iostream>
#include"leaf.h"


template<class T>
class tree
{
public:
	leaf<T>* topleaf=nullptr;
	int leafnum = 0;
public:
	tree();
	~tree();
	leaf<T>* idtoleaf(leaf<T>* top,int id);//����idѰ��Ҷ��
	void addleaf(T value);//����Ҷ��
	void showtreehouxu(leaf<T>* top);//������������������ʾ������
	void showtreeqianxu(leaf<T>* top);//ǰ��������������ʾ������
	void showtreezhongxu(leaf<T>* top,int grade=0);//����������������ʾ������
};

