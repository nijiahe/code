#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class T>
class hashnode
{
public:
	int key;//����
	vector<T> dataptr;
	int looked_time;//������Ҵ���
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

//ÿ���ڵ��а����ڵ������,�����洢������