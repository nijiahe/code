#ifndef LISTNODE_H
#define LISTNODE_H

#include"linklist.h"

template<class T> class linklist;

template<class T>
class listnode
{
private:
	T mdata;
	listnode<T>* mnext;
public:
	listnode()
	{

	}

	~listnode()
	{

	}

	friend class linklist<T>;
};

#endif // LISTNODE_H
