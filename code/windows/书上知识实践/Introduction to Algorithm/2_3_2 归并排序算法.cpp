#include "common.h"
#include <vector>

//[lo,mid)and[mid,hi)
template<typename T>
void merge(T* arr,int lo, int mid, int hi, bool(*COMPARED)(T, T)) {
	T* A = arr + lo;
	T* B = new T[mid - lo];
	T* C = arr + mid;
	int la = hi - lo, lb = mid - lo, lc = hi - mid;
	
	for (int i = 0; i < lb; i++)B[i] = A[i];//����

	//i,j,k�ֱ�ָ��A,B,C�е�Ԫ��
	int i = 0, j = 0, k = 0;
	for (int j = 0; j < lb;)//B�ﻨ��,���������,��Ϊʣ���C��Ĳ��ֱض���������
		A[i++] = ((k >= lc) || COMPARED(B[j],C[k])) ? B[j++] : C[k++];//���C���滨����,����C����ָ��Ĵ�,��ȡB���
	delete []B;
}

//[lo,hi)
template<typename T>
void mergeSort(T* arr, int lo, int hi,bool(*COMPARED)(T,T)) {
	if (hi - lo < 2)//�ݹ��
		return;
	int mid = (lo + hi) / 2;
	mergeSort(arr, lo, mid, COMPARED);
	mergeSort(arr, mid, hi, COMPARED);
	merge(arr, lo, mid, hi, COMPARED);
}

int main2_3_2() {
	vector<int> arr;
	for (int i = 0; i < 10; i++) {
		arr.push_back(rand() % 100);
	}
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	mergeSort<int>(&arr[0], 0, arr.size(), [](int prev, int next)->bool {
		return prev < next;
	});
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	mergeSort<int>(&arr[0], 0, arr.size(), [](int prev, int next)->bool {
		return prev > next;
	});
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	return 0;
}