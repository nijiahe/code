#pragma once

#include "Vector.h"

template<typename T>
class Stack :public Vector<T> {
public:
	void push(T const& val);
	T pop();
	T& get();
};

#include "Stack_implenmentation.h"
#include "Stack_algorithm.h"