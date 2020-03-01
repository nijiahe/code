#pragma once

#include "Stack.h"

template<typename T>
void Stack<T>::push(T const& val) {
	this->insert(val);
}

template<typename T>
T Stack<T>::pop() {
	return this->remove(this->size() - 1);
}

template<typename T>
T& Stack<T>::get() {
	return (*this)[this->size()-1];
}