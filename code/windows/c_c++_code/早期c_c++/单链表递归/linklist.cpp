#include "linklist.h"/*��ģ��ķ����ļ��е�ÿ������Ҳ��Ҫ����ģ��,�������Ǹ�ģ���࣬��Ϊģ����һ��ʼ�ǲ����ڵģ������ڵ�����ֻ�ܴ��ڲ����ڵĺ���*/

template<class T>
linklist<T>::linklist()
{
	this->topnode = nullptr;
	this->tailnode = nullptr;
	cout << "listnode creat" << endl;
}
template<class T>
linklist<T>::~linklist()
{
	cout << "listnode delete" << endl;
}

template<class T>
void linklist<T>::ListInsertHead(T value)//��ͷ������ڵ�
{
	listnode<T>* pnode = new listnode<T>();//newһ���ڵ㣬��pnode��������
	pnode->mdata = value;
	pnode->mnext = nullptr;//�Խڵ���г�ʼ��
	if (this->topnode == nullptr&&this->tailnode == nullptr)//��������б����ͷ�ڵ��β�ڵ�Ϊ��
	{
		this->topnode = pnode;//ͷ�ڵ��ɴ��������
		this->tailnode = pnode;//β�ڵ��ɴ��������
		return;
	}
	else
	{
		pnode->mnext = this->topnode;//�ڵ��е���һ����Ϊԭ����ͷ�ڵ�
		this->topnode = pnode;//�����б����ͷ�ڵ��Ϊ���������
		return;
	}
}
template<class T>
void linklist<T>::ListInsertTail(T value)
{
	listnode<T>* pnode = new listnode<T>;
	pnode->mdata = value;
	pnode->mnext = nullptr;
	if (this->topnode == nullptr&&this->tailnode == nullptr)//��������б����ͷ�ڵ��β�ڵ�Ϊ��
	{
		this->topnode = pnode;//ͷ�ڵ��ɴ��������
		this->tailnode = pnode;//β�ڵ��ɴ��������
		return;
	}
	else
	{
		this->tailnode->mnext = pnode;//�����б����β�ڵ����һ����Ϊ���������
		this->tailnode = pnode;//�����б����β�ڵ��Ϊ���������
		return;
	}
}
template<class T>
void linklist<T>::ListSort(bool flag)//flag=trulʱ�Ӵ�С��flag=falseʱ��С����
{
	if (this->topnode == nullptr&&this->tailnode == nullptr)
	{
		return;
	}
	else
	{
		if (flag)
		{
			for (listnode<T>* p1 = this->topnode; p1 != nullptr; p1 = p1->mnext)//ð������
			{
				for (listnode<T>* p2 = p1; p2 != nullptr; p2 = p2->mnext)
				{
					if (p1->mdata<p2->mdata)
					{
						p1->mdata = p1->mdata + p2->mdata;
						p2->mdata = p1->mdata - p2->mdata;
						p1->mdata = p1->mdata - p2->mdata;
					}
				}
			}
			return;
		}
		else
		{
			for (listnode<T>* p1 = topnode; p1 != nullptr; p1 = p1->mnext)//ð������
			{
				for (listnode<T>* p2 = this->topnode; p2 != nullptr; p2 = p2->mnext)
				{
					if (p1->mdata>p2->mdata)
					{
						p1->mdata = p1->mdata + p2->mdata;
						p2->mdata = p1->mdata - p2->mdata;
						p1->mdata = p1->mdata - p2->mdata;
					}
				}
			}
			return;
		}
		return; \
	}
}
template<class T>
void linklist<T>::ListShow()//����������нڵ�
{
	if (this->topnode == nullptr&&this->tailnode == nullptr)
	{
		return;
	}
	else
	{
		if (this->topnode->mnext == nullptr)
		{
			std::cout << "1->" << topnode->mdata << std::endl;
			return;
		}
		else
		{
			listnode<T>* pnode = this->topnode;
			int i = 1;
			while (pnode->mnext != nullptr)
			{
				std::cout << i << ". " << pnode->mdata << std::endl;//���Ŀ¼������
				i++;
				pnode = pnode->mnext;
			}
			std::cout << i << ". " << pnode->mdata << std::endl;
			return;
		}
	}
}
template<typename T>
listnode<T> *linklist<T>::ListFindIndex(int index)//����Ŀ¼�����ؽڵ��ַ
{
	if (index <= 0)
	{
		std::cout << "index cannot must > 0" << std::endl;
		return nullptr;
	}
	listnode<T>* pnode = topnode;
	int i = 1;
	while (pnode != nullptr)
	{
		if (i == index)
		{
			return pnode;
		}
		pnode = pnode->mnext;
		i++;
	}
	return nullptr;
}
template<class T>
listnode<T> *linklist<T>::ListFindValue(T value)//���ݴ洢��ֵ���ص�һ��ƥ��Ľڵ�ĵ�ַ
{
	listnode<T>* pnode = topnode;
	while (pnode != nullptr)
	{
		if (pnode->mdata == value)
		{
			return pnode;
		}
		pnode = pnode->mnext;
	}
	return nullptr;
}
/*template<class T>
void linklist<T>::ListRemove(int index)//����Ŀ¼��ɾ���ڵ�
{
	if (index <= 0)
	{
		std::cout << "index cannot must > 0" << std::endl;
		return;
	}
	if (index == 1)
	{
		if (topnode->mnext == nullptr)
		{
			topnode->mnext = nullptr;
			return;
		}
		else
		{
			listnode<T>* xnode = this->topnode;
			this->topnode = this->topnode->mnext;
			delete xnode;
			xnode = nullptr;
			return;
		}
	}
	else
	{
		listnode<T>* pnode = topnode;
		int i = 1;
		while (pnode->mnext != nullptr)//���topnode->mnext=nullptr,��index!=1,ֱ�ӷ���
		{
			if (i == index - 1)
			{
				listnode<T>* tnode = pnode->mnext;
				pnode->mnext = tnode->mnext;
				tnode->mnext = nullptr;
				delete tnode;
			}
			pnode = pnode->mnext;
			i++;
		}
		return;
	}
}*/
template<class T>
void linklist<T>::ListRemove(listnode<T>* valuenode)//���ݽڵ��ַɾ���ڵ�
{
	if (topnode == valuenode)
	{
		listnode<T>* tnode = topnode;
		topnode = topnode->mnext;
		tnode->mnext = nullptr;
		delete tnode;
		return;
	}
	else
	{
		listnode<T>* pnode = this->topnode;
		while (pnode->mnext != nullptr)
		{
			if (pnode->mnext == valuenode)
			{
				listnode<T>* xnode = pnode->mnext;
				pnode->mnext = xnode->mnext;
				xnode->mnext = nullptr;
				delete xnode;
				return;
			}
			pnode = pnode->mnext;
		}
		return;
	}
}
template<class T>
void linklist<T>::ListRemove(T value)//����ֵɾ����һ��ƥ��Ľڵ�
{
	listnode<T>* pnode = this->ListFindValue(value);
	if (pnode == nullptr)
	{
		return;
	}
	this->ListRemove(pnode);
	return;
}
template<class T>
void linklist<T>::ListRevise(int index, T value)
{
	listnode<T>* pnode = this->ListFindIndex(index);
	if (pnode == nullptr)
	{
		return;
	}
	pnode->mdata = value;
}
template<class T>//��ģ����Ԫ��������
void run(linklist<T> &it)
{
	std::cout << "run" << std::endl;
	it.ListShow();
}
template<class T>
void linklist<T>::ListInsertIndex(int index, T value)//����Ŀ¼����Ŀ¼���������һ���ڵ�
{
	listnode<T>* pnode = this->ListFindIndex(index);
	if (pnode == nullptr)
	{
		return;
	}
	listnode<T>* pnewnode = new listnode<T>;
	pnewnode->mdata = value;
	if (pnode->mnext == nullptr)
	{
		pnode->mnext = pnewnode;
		pnewnode->mnext = nullptr;
		return;
	}
	else
	{
		listnode<T>* tnode = pnode->mnext;
		pnode->mnext = pnewnode;
		pnewnode->mnext = tnode;
		return;
	}
}


template<class T>
T linklist<T>::Maxkey(int n)//n����������ͷ�����������ֵ
{
	if (n == 1)
	{
		return topnode->mdata;
	}
	T temp = Maxkey(n - 1);
	if (this->ListFindIndex(n)->mdata>=Maxkey(n-1))
	{
		return this->ListFindIndex(n)->mdata;
	}
	return Maxkey(n - 1);
}

template<class T>
int linklist<T>::nodecount(listnode<T>* node)/*��ڵ����*/
{
	if (tailnode == node)
	{
		return 1;
	}
	return nodecount(node->mnext) + 1;
}
template<class T>
double linklist<T>::Average(int n)//ͨ���ݹ���ƽ��ֵ
{
	if (n == 1)
	{
		return (double)this->topnode->mdata;
	}
	return (double)(Average(n - 1)*(n - 1) + this->ListFindIndex(n)->mdata) / n;
}