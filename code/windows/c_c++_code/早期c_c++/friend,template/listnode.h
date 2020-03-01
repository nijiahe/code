#ifndef LISTNODE_H
#define LISTNODE_H

#include"linklist.h"

template<class T> class linklist;//友元的是个模板就需要在定义类之前声明

template<class T>
class listnode
{
private:
	T mdata;
public:
	listnode<T>* mnext;
	listnode()
	{

	}

	~listnode()
	{

	}
	friend class linklist<T>;
};

#endif // LISTNODE_H
