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

/*����һ������,�ù�ϣ�ڵ�ÿ���ڵ�������ʼ��Ϊ1 2 3 ����,�洢�����ݵ��������е�����,���Ҵ���=0*/
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
