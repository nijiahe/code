#include "linklist.h"/*类模板的方法文件中的每个函数也需要加上模板,代表这是个模板类，因为模板类一开始是不存在的，不存在的类中只能存在不存在的函数*/

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
void linklist<T>::ListInsertHead(T value)//在头部插入节点
{
	listnode<T>* pnode = new listnode<T>();//new一个节点，用pnode保存数据
	pnode->mdata = value;
	pnode->mnext = nullptr;//对节点进行初始化
	if (this->topnode == nullptr&&this->tailnode == nullptr)//如果链表中保存的头节点和尾节点为空
	{
		this->topnode = pnode;//头节点变成创建的这个
		this->tailnode = pnode;//尾节点变成创建的这个
		return;
	}
	else
	{
		pnode->mnext = this->topnode;//节点中的下一个变为原来的头节点
		this->topnode = pnode;//链表中保存的头节点变为创建的这个
		return;
	}
}
template<class T>
void linklist<T>::ListInsertTail(T value)
{
	listnode<T>* pnode = new listnode<T>;
	pnode->mdata = value;
	pnode->mnext = nullptr;
	if (this->topnode == nullptr&&this->tailnode == nullptr)//如果链表中保存的头节点和尾节点为空
	{
		this->topnode = pnode;//头节点变成创建的这个
		this->tailnode = pnode;//尾节点变成创建的这个
		return;
	}
	else
	{
		this->tailnode->mnext = pnode;//链表中保存的尾节点的下一个变为创建的这个
		this->tailnode = pnode;//链表中保存的尾节点变为创建的这个
		return;
	}
}
template<class T>
void linklist<T>::ListSort(bool flag)//flag=trul时从大到小，flag=false时从小到大
{
	if (this->topnode == nullptr&&this->tailnode == nullptr)
	{
		return;
	}
	else
	{
		if (flag)
		{
			for (listnode<T>* p1 = this->topnode; p1 != nullptr; p1 = p1->mnext)//冒泡排序法
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
			for (listnode<T>* p1 = topnode; p1 != nullptr; p1 = p1->mnext)//冒泡排序法
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
void linklist<T>::ListShow()//遍历输出所有节点
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
				std::cout << i << ". " << pnode->mdata << std::endl;//输出目录和数据
				i++;
				pnode = pnode->mnext;
			}
			std::cout << i << ". " << pnode->mdata << std::endl;
			return;
		}
	}
}
template<typename T>
listnode<T> *linklist<T>::ListFindIndex(int index)//根据目录数返回节点地址
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
listnode<T> *linklist<T>::ListFindValue(T value)//根据存储的值返回第一个匹配的节点的地址
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
void linklist<T>::ListRemove(int index)//根据目录数删除节点
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
		while (pnode->mnext != nullptr)//如果topnode->mnext=nullptr,且index!=1,直接返回
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
void linklist<T>::ListRemove(listnode<T>* valuenode)//根据节点地址删除节点
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
void linklist<T>::ListRemove(T value)//根据值删除第一个匹配的节点
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
template<class T>//类模板友元函数测试
void run(linklist<T> &it)
{
	std::cout << "run" << std::endl;
	it.ListShow();
}
template<class T>
void linklist<T>::ListInsertIndex(int index, T value)//根据目录数在目录数后面添加一个节点
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
T linklist<T>::Maxkey(int n)//n代表求链表头几个数的最大值
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
int linklist<T>::nodecount(listnode<T>* node)/*求节点个数*/
{
	if (tailnode == node)
	{
		return 1;
	}
	return nodecount(node->mnext) + 1;
}
template<class T>
double linklist<T>::Average(int n)//通过递归求平均值
{
	if (n == 1)
	{
		return (double)this->topnode->mdata;
	}
	return (double)(Average(n - 1)*(n - 1) + this->ListFindIndex(n)->mdata) / n;
}