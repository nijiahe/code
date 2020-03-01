#pragma once

#include"tree.h"

template<class T>class tree;

template<class T>
class leaf
{
public:
	int id;
	T value;
	leaf<T>* leftleaf = nullptr;
	leaf<T>* rightleaf = nullptr;
public:
	leaf()
	{

	}
	leaf(T value):value(value)
	{

	}
private:
	~leaf()
	{

	}
	friend class tree<T>;
};

