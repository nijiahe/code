#ifndef LISTNODE_H
#define LISTNODE_H

#include"linklist.h"

template<class T> class linklist;//��Ԫ���Ǹ�ģ�����Ҫ�ڶ�����֮ǰ����

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
