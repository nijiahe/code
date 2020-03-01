#pragma once

#include "Vector.h"

//kѡȡ�㷨,����O(n^2),ƽ������O(n),c++���ݽṹ���н����ǸĽ�Ϊ����ҲΪO(n)��,���ı������ѡȡ���,��Ϊѡȡ��λ������λ��
//����Ƶ�ｲ�������δ�Ľ���
template<typename T>
void quickSelect(Vector<T>& A, int k) {
	int lo = 0, hi = A.size() - 1;
	//[lo,hi]����˵�ǰѰ�����ķ�Χ
	while (lo < hi) {
		int i = lo, j = hi;//iһ��ʼ��ָ���(A[lo]�����,��������)
		T pivot = A[lo];//A[lo]��Ϊ���
		while (i < j) {
			while ((i < j) && (pivot<=a[j]))//�����ǰj�������
				j--;//��֮����
			//����A[j]���λ����λ��
			a[i] = a[j];//��ʱ��λ��������A[j]��
			while ((i < j) && (pivot >= a[i]))//ͬ��,��i����Ҳһ��һ������
				i++;
			a[j] = a[i];//��������ķŵ���λ��
		}
		//��ʱi=j,������֮,��������ǲ���ȥ��
		if (k < i)hi = i - 1;
		if (k > i)li + 1;
	}
	//��ʱlo=hi,A[k]����ľ��ǰ�˳�����е�k
}