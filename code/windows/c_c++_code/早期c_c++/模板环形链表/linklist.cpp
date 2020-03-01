#include "linklist.h"
#include<iostream>

using namespace std;

template<class T>
linklist<T>::linklist()
{
	this->ports = nullptr;
	this->listlong = 0;
}

template<class T>
linklist<T>::~linklist()
{
	this->clean();
}

template<class T>
listnode<T>* linklist<T>::pushback(T value)//��β������
{
	listnode<T>* node = new listnode<T>;
	node->data = value;
	if (this->ports == nullptr)
	{
		this->ports = node;
		node->nextnode = ports;
		this->listlong += 1;
	}
	else
	{
		listnode<T>* temp = ports->nextnode;
		while (temp->nextnode != ports)
		{
			temp = temp->nextnode;
		}
		temp->nextnode = node;
		node->nextnode = this->ports;
		this->listlong+=1;
	}
	return node;
}

template<class T>
listnode<T>* linklist<T>::indexinsert(int index,T value)//����Ŀ¼������
{
	listnode<T>* temp = this->findindex(index);
	if (temp == nullptr)
	{
		return nullptr;
	}
	listnode<T>* newnode= new listnode<T>;
	newnode->data = value;
	listnode<T>* temp2 = temp->nextnode;
	temp->nextnode = newnode;
	newnode->nextnode = temp2;
	this->listlong += 1;
	return newnode;
}

template<class T>
listnode<T>* linklist<T>::revise(int index, T value)//����Ŀ¼���޸�
{
	listnode<T>* temp = this->findindex(index);
	if (temp == nullptr)
	{
		return nullptr;
	}
	temp->data = value;
	return temp;
}

template<class T>
listnode<T>* linklist<T>::findindex(int index)//����Ŀ¼����,���ؽڵ��ַ
{
	if (index == 1)
	{
		return this->ports;
	}
	if (index > this->listlong||index<=0)
	{
		return nullptr;
	}
	listnode<T>* temp = this->ports->nextnode;
	int walk = 2;
	while (walk!=index)
	{
		temp = temp->nextnode;
		walk++;
	}
	return temp;
}

template<class T>
listnode<T>* linklist<T>::findvalue(T value)//������������ݲ���
{
	if (ports->data == value)
	{
		return ports;
	}
	listnode<T>* temp = ports->nextnode;
	while (temp != ports)
	{
		if (temp->data == value)
		{
			return temp;
		}
		temp++;
	}
	return nullptr;
}

template<class T>
void linklist<T>::merge(linklist<T> anotherlist)//��������������ϲ�
{

}

template<class T>
bool linklist<T>::remove(int index)//����Ŀ¼��ɾ��
{
	if (index == 1)
	{
		listnode<T>* temp = ports;
		while (temp->nextnode != ports)
		{
			temp = temp->nextnode;
		}
		temp->nextnode = ports->nextnode;
		ports->nextnode = nullptr;
		delete ports;
		ports = temp->nextnode;
		this->listlong -= 1;
	}
	else
	{
		listnode<T>* temp = this -> findindex(index - 1);
		if (temp == nullptr)
		{
			return 0;
		}
		listnode<T>* temp2 = temp->nextnode->nextnode;
		delete temp->nextnode;
		temp->nextnode = temp2;
		this->listlong -= 1;
	}
	return 1;
}

template<class T>
bool linklist<T>::remove(listnode<T>* remnode)//���ݴ���Ľڵ�ɾ��ɾ��
{
	if (remnode == ports)
	{
		this->remove(1);
		return 1;
	}
	else
	{
		listnode<T>* temp = ports;
		while (temp->nextnode != ports)
		{
			if (temp->nextnode == remnode)
			{
				listnode<T>* temp2 = temp->nextnode->nextnode;
				delete temp->nextnode;
				temp->nextnode = temp2;
				listlong -= 1;
				return 1;
			}
			temp = temp->nextnode;
		}
		return 0;
	}
}

template<class T>
void linklist<T>::listshow()//��ʾ��������Ԫ��
{
	if (this->ports == nullptr)
	{
		cout << "nullptr" << endl;
		return;
	}
	listnode<T>*  temp = ports->nextnode;
	cout << ports->data << endl;
	while (temp != ports)
	{
		cout << temp->data << endl;
		temp = temp->nextnode;
	}
}

template<class T>
void linklist<T>::rev()//��ת����
{

}

template<class T>
int linklist<T>::getlistlong()//��������Ԫ����
{
	return listlong;
}

template<class T>
void linklist<T>::clean()//�������
{

}