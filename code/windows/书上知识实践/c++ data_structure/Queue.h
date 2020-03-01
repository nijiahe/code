#pragma once

#include "List.h"

template<typename T>
class Queue :public List<T> {
public:
	void enqueue(T const& val) { this->insertAsLast(val); }
	T dequeue() { return this->remove(this->first()); }
	T& front() { return this->first()->_data; }
};