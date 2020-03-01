#include "tree.h"

template<class T>
tree<T>::tree()
{
}

template<class T>
tree<T>::~tree()
{
}

template<class T>
void tree<T>::addleaf(T value)
{
	leaf<T>* Leaf = new leaf<T>;
	Leaf->value = value;
	Leaf->id = leafnum + 1;
	if (topleaf == nullptr)
	{
		topleaf = Leaf;
		leafnum++;
	}
	else
	{
		leaf<T>* father = idtoleaf(topleaf, (leafnum + 1) / 2);
		if ((leafnum + 1) % 2 == 0)
		{
			father->leftleaf = Leaf;
		}
		else
		{
			father->rightleaf = Leaf;
		}
		leafnum++;
	}
}

template<class T>
void tree<T>::showtreehouxu(leaf<T>* top)
{
	if (top->leftleaf != nullptr)
	{
		showtreehouxu(top->leftleaf);
	}
	if (top->rightleaf != nullptr)
	{
		showtreehouxu(top->rightleaf);
	}
	cout << "Ò¶×Óid:" << top->id << " value:" << top->value << endl;
}

template<class T>
void tree<T>::showtreeqianxu(leaf<T>* top)
{
	cout << "Ò¶×Óid:" << top->id << " value:" << top->value << endl;
	if (top->leftleaf != nullptr)
	{
		showtreeqianxu(top->leftleaf);
	}
	if (top->rightleaf != nullptr)
	{
		showtreeqianxu(top->rightleaf);
	}
}

template<class T>
void tree<T>::showtreezhongxu(leaf<T>* top,int grade)
{
	if (top->leftleaf != nullptr)
	{
		showtreezhongxu(top->leftleaf,grade+1);
	}
	for (int i = 0; i < grade; i++)
	{
		cout << "  ";
	}
	cout << "Ò¶×Óid:" << top->id << " value:" << top->value << endl;
	if (top->rightleaf != nullptr)
	{
		showtreezhongxu(top->rightleaf,grade+1);
	}
}

template<class T>
leaf<T>* tree<T>::idtoleaf(leaf<T>* top, int id)
{
	if (id == 1)
	{
		return top;
	}
	int num = id % 2;
	id /= 2;
	if (num == 0)
	{
		return idtoleaf(top, id)->leftleaf;
	}
	if (num == 1)
	{
		return idtoleaf(top, id)->rightleaf;
	}
	if (id <= 0)
	{
		return nullptr;
	}
}