#pragma once

//优先级队列基类,priority queue
template<typename T>
struct PQ {
	virtual void insert(T e) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};