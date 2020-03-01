#pragma once
template<class T> class linklist;

template<class T>
class listnode
{
public:
	T data;
	listnode<T>* nextnode;
	listnode()
	{

	}
	~listnode()
	{
		
	}
	friend class linklist<T>;
};

