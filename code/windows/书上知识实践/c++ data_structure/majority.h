#pragma once

#include "Vector.h"

//�����㷨,������ʾռһ�����ϵ���

//�ҳ���ѡ��
template<typename T>
T majEleCandidate(Vector<T> &A) {
	int c = 0; T maj;//c��ʾ��ǰmaj�ȷ�maj�������
	for (int i = 0; i < A.size(); i++) {
		if (0 == c) {
			maj = A[i]; c = 1;
		}
		else
			(maj == A[i]) ? c++ : c--;//���¼���ֵ
	}
	return maj;
}

template<typename T>
bool majEleCheck(Vector<T>& A, T maj) {
	int occurence = 0;
	for (int i = 0; i < A.size(); i++)
		if (A[i] == maj)
			occurence++;//ͳ�Ƹ���
	return 2 * occurence > A.size();
}

template<typename T>
bool majority(Vector<T> &A, T &maj) {
	maj = majEleCandidate(A);
	return majEleCheck(A, maj);
}