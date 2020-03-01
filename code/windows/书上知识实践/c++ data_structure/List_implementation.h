#pragma once

#include "List.h"
#include <cstdio>

template<typename T>
void List<T>::init() {
	_size = 0;
	_header = new ListNode<T>;
	_trailer = new ListNode<T>;
	_header->_succ = _trailer; _header->_pred = nullptr;
	_trailer->_pred = _header; _trailer->_succ = nullptr;
}

template<typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (0 < _size)
		remove(_header->_succ);
	return oldSize;
}

template<typename T>
void List<T>::copyNodes(ListNode<T>* node, int n) {
	init();
	while ((node->_succ) && n--) {
		insertAsLast(node->_data);
		node = node->_succ;
	}
}

template<typename T>
void List<T>::merge(ListNode<T>*& p1, int n1, List<T>& L, ListNode<T>* p2, int n2) {
	ListNode<T>* temp = p1->_pred;
	while (0 < n1 - 1) {
		if ((0 < n2 - 1) && (p1->_data <= p2->_data)) {
			if (p2 == (p1 = p1->_succ)) //L就是*this的情况，这样表示前后已经连接起来了，已经排好了
				break;
			n1--;
		}
		else {
			insertB(p2, L.remove((p2 = p2->_succ)->_pred)); n2--;
		}
	}
	p1 = temp->_succ;
}

template<typename T>
void List<T>::mergeSort(ListNode<T>*& p, int n) {//归并排序，分而治之思想，O(nlogn)
	if (n <= 1)return;
	int m = n / 2;
	ListNode<T>* q = p;
	for (int i = 0; i < m; i++)q = q->_succ;
	mergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template<typename T>
void List<T>::selectionSort(ListNode<T>* node, int n) {
	ListNode<T>* head = node->_pred, *tail = node;
	for (int i = 0; i < n; i++)node = node->_succ;
	while (0 < n) {
		ListNode<T>* maxNode = selectMax(head->_succ, n--);
		if (maxNode == tail->_pred)continue;
		else {
			swapNode(maxNode, tail->_pred);
			tail = tail->_pred;
		}
	}
}

template<typename T>
void List<T>::insertionSort(ListNode<T>* p, int n) {
	for (int r = 0; r < n; r++) {
		insertA(search(p->_data, r, p), p->_data);
		p = p->_succ; remove(p->_pred);
	}
}

template<typename T>
ListNode<T>* List<T>::getNodeByRank(Rank r) const {
	ListNode<T>* _temp = _header->_succ;
	while (0 < r--)
		_temp = _temp->_succ;
	return _temp;
}

template<typename T>
void List<T>::swapNode(ListNode<T>* n1, ListNode<T>* n2) {
	std::swap(n1->_pred->_succ, n2->_pred->_succ);
	std::swap(n1->_succ->_pred, n2->_succ->_pred);
	std::swap(n1->_succ, n2->_succ);
	std::swap(n1->_pred, n2->_pred);
}

template<typename T>
List<T>::List() { init(); }

template<typename T>
List<T>::List(List<T> const& L) {
	copyNodes(L._header, L._size);
}

template<typename T>
List<T>::List(List<T> const& L, Rank r, int n) {
	copyNodes(L.getNodeByRank(r), n);
}

template<typename T>
List<T>::List(ListNode<T>* p, int n) {
	copyNodes(p, n);
}

template<typename T>
List<T>::~List() {
	clear();
	delete _header;
	delete _trailer;
}

template<typename T>
T& List<T>::operator[] (Rank r) const {
	return getNodeByRank(r)->_data;
}

template<typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const {//无序区间查找，在节点p的n个真前驱中找到e的最后者
	while ( 0 < n--) 
		if ( (p = p->_pred)->_data == e)return p;
	
	return nullptr;
}

template<typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const {//在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
	do {
		p = p->_pred; n--;
	} while ((p->_data > e) && (-1<n));
	return p;
}

template<typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n) {
	ListNode<T>* temp = p;
	for (ListNode<T>* cur = p; 1 < n; n--) {
		if ((cur = cur->_succ)->_data >= temp->_data)temp = cur;
	}
	return temp;
}

template<typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e) {
	return insertA(_header, e);
}

template<typename T>
ListNode<T>* List<T>::insertAsLast(T const& e) {
	return insertB(_trailer, e);
}

template<typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e) {
	ListNode<T>* _node = new ListNode<T>(e, p, p->_succ);
	p->_succ->_pred = _node;
	p->_succ = _node;
	_size++;
	return _node;
}

template<typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e) {
	ListNode<T>* _node = new ListNode<T>(e, p->_pred, p);
	p->_pred->_succ = _node;
	p->_pred = _node;
	_size++;
	return _node;
}

template<typename T>
T List<T>::remove(ListNode<T>* p) {
	T val = p->_data;
	p->_pred->_succ = p->_succ;
	p->_succ->_pred = p->_pred;
	_size--;
	delete p;
	return val;
}

template<typename T>
void List<T>::sort(ListNode<T>* p, int n) {
	int num = std::rand();
	switch (num %3)
	{
	case 1:
		mergeSort(p, n); 
		break;
	case 2:
		insertionSort(p, n); 
		break;
	default:
		selectionSort(p, n);
		break;
	}
}

template<typename T>
int List<T>::deduplicate() {
	ListNode<T>* p = _header->_succ;
	T _oldSize = _size;
	for (Rank r = 0; p != _trailer; p = p->_succ) {
		ListNode<T>* q = find(p->_data, r, p);
		q ? remove(q) : r++;
	}
	return _oldSize - _size;
}

template<typename T>
int List<T>::uniquify() {
	if (_size < 2)return 0;
	ListNode<T>* p = first();
	ListNode<T>* q;
	T _oldSize = _size;
	while (_trailer != (q = p->_succ)) {
		if (p->_data = q->_data)
			remove(q);
		else p = q;
	}
	return _oldSize - _size;
}

template<typename T>
void List<T>::reverse() {
	ListNode<T>* p = _header->_succ;
	while (p != _trailer) {
		std::swap(p->_pred, p->_succ);
		p = p->_pred;
	}
}

template<typename T>
void List<T>::traverse(void(*visit) (T&)) {
	ListNode<T>* p = _header;
	while ((p = p->_succ) != _trailer)
		visit(p->_data);
}

template<typename T>
template <typename VST> void List<T>::traverse(VST& visit) {
	ListNode<T>* p = _header;
	while ((p = p->_succ) != _trailer)
		visit(p->_data);
}