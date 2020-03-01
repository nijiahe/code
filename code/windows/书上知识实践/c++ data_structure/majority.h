#pragma once

#include "Vector.h"

//众数算法,众数表示占一半以上的数

//找出候选者
template<typename T>
T majEleCandidate(Vector<T> &A) {
	int c = 0; T maj;//c表示当前maj比非maj多的数量
	for (int i = 0; i < A.size(); i++) {
		if (0 == c) {
			maj = A[i]; c = 1;
		}
		else
			(maj == A[i]) ? c++ : c--;//更新计量值
	}
	return maj;
}

template<typename T>
bool majEleCheck(Vector<T>& A, T maj) {
	int occurence = 0;
	for (int i = 0; i < A.size(); i++)
		if (A[i] == maj)
			occurence++;//统计个数
	return 2 * occurence > A.size();
}

template<typename T>
bool majority(Vector<T> &A, T &maj) {
	maj = majEleCandidate(A);
	return majEleCheck(A, maj);
}