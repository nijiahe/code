#pragma once

#include "QuadlistNode.h"

//������,T��һ�ִ�������
template<typename T>
class Quadlist {
private:
	int _size;//��С
	QuadlistNode<T>* header;//ͷ�ڱ�
	QuadlistNode<T>* trailer;//β�ڱ�

protected:
	void init();//��ʼ��
	int clear();//������нڵ�

public:
	Quadlist() { init(); }//���캯��
	~Quadlist() { clear(); delete header; delete trailer; }//��������

	int size() const { return _size; }
	bool empty() const { return _size <= 0; }

	QuadlistNode<T>* first() const { return header->succ; } //�׽ڵ�λ��
	QuadlistNode<T>* last() const { return trailer->pred; } //ĩ�ڵ�λ��
	bool valid(QuadlistNode<T>* p) //�ж�λ��p�Ƿ����Ϸ�
	    { return p && (trailer != p) && (header != p); }

	// ��д���ʽӿ�
	T remove(QuadlistNode<T>* p); //ɾ�����Ϸ���λ��p���Ľڵ㣬���ر�ɾ���ڵ����ֵ
	QuadlistNode<T>* insertAfterAbove(T const& e, QuadlistNode<T>* p, QuadlistNode<T>* b = nullptr);//��e��Ϊp�ĺ�̡�b�����ڲ���
	
	//����
	void traverse(void(*) (T&)); //�������ڵ㣬����ʵʩָ������������ָ�룬ֻ����ֲ��޸ģ�
	template < typename VST>void traverse(VST&); //�������ڵ㣬����ʵʩָ���������������󣬿�ȫ�����޸Ľڵ㣩
};

#include "Quadlist_inplenmentation.h"