#include "Hash.h"


using namespace std;

template<class T>
Hash<T>::Hash(int indexlong)
{
	this->indexlong = indexlong;
	p = new hashnode<T>[indexlong];
	for (int i = 0; i < indexlong; i++)
	{
		p[i].key = i;
	}
}

template<class T>
Hash<T>::~Hash()
{
	delete[]p;
}

/*传入一个数组,让哈希节点每个节点索引初始化为1 2 3 ……,存储的数据等于数组中的数据,查找次数=0*/
template<class T>
void Hash<T>::init(T* pt)
{
	for (int i = 0; pt[i] != '\0'; i++)
	{
		int key = pt[i] % indexlong;
		this->p[key].dataptr.push_back(pt[i]);
	}
}
template<class T>
hashnode<T>* Hash<T>::find(T value)
{
	int key = value%indexlong;
	return &p[key];
}
