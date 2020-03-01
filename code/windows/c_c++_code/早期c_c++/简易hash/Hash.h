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
	hashnode<T>* p;//存储N个哈希表的节点
	int indexlong;//索引长度
public:
	Hash(int indexlong=10);
	~Hash();
	void init(T* pt);//将一个数组装进hash表
	hashnode<T>* find(T value);
};

