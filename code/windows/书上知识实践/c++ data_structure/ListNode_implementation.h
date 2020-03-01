#pragma once

#include "ListNode.h"

template<typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e) {
	ListNode<T>* _newNode = new ListNode<T>(e,_pred,_succ);
	_pred->_succ = _newNode;
	_succ->_pred = _newNode;
	return _newNode;
}

template<typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e) {
	ListNode<T>* _newNode = new ListNode<T>(e, _pred, _succ);
	_pred->_succ = _newNode;
	_succ->_pred = _newNode;
	return _newNode;
}