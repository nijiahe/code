#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class T>
class hashnode
{
public:
	int key;//索引
	vector<T> dataptr;
	int looked_time;//代表查找次数
	hashnode()
	{
		key = 0;
		looked_time = 0;
	}
	~hashnode()
	{
	}
	void vecshow()
	{
		
	}
};

//每个节点中包含节点的索引,索引存储的数据