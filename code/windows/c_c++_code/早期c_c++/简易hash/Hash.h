#pragma once
#include<vector>
#include"hashnode.h"
#include<iostream>
#include<algorithm>

using namespace std;

template<class T>
class Hash
{
public:
	hashnode<T>* p;//�洢N����ϣ��Ľڵ�
	int indexlong;//��������
public:
	Hash(int indexlong=10);
	~Hash();
	void init(T* pt);//��һ������װ��hash��
	hashnode<T>* find(T value);
};

