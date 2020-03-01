#pragma once

template<typename T>
class ListNode
{
public:
	// ��Ա
	T _data; //����
	ListNode<T>* _pred; //ǰ��
	ListNode<T>* _succ; //���
	// ���캯��
	ListNode() {} //���header��trailer�Ĺ���
	ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr): _data(e), _pred(p), _succ(s) {} //Ĭ�Ϲ�����
	// �����ӿ�
	ListNode<T>* insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNode<T>* insertAsSucc(T const& e); //���浱ǰ�ڵ�֮������½ڵ�
};

#include "ListNode_implementation.h"