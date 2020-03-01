#include "Vector.h"
#include <cstdio>
#include <iostream>
#include "PQ_ComplHeap.h"

template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 *(hi - lo)];
	_size = 0;
	while (lo < hi) {
		_elem[_size++] = A?A[lo]:0;
		lo++;
	}
}

template<typename T>
void Vector<T>::expand() {
	if (_size < _capacity)return;//С�ڵ�ʱ�����ݣ����ھ�Ҫ������
	_capacity = _capacity > DEFAULT_CAPACITY ? _capacity : DEFAULT_CAPACITY;
	T * _oldelem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = _oldelem[i];
	delete[]_oldelem;
}

template<typename T>
void Vector<T>::shrink() {
	if (_capacity <= DEFAULT_CAPACITY)return;
	if (_capacity < _size >> 2)return;
	T* _oldelem = _elem;
	copyFrom(_oldelem, 0, _size);
	delete[]_oldelem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool flag = false;
	Rank last = lo;
	if (hi <= lo + 1)return flag;
	for (int i = lo; i < hi - 1; i++)
		if (_elem[i] > _elem[i + 1]) {
			std::swap(_elem[i], _elem[i + 1]);
			flag = true;
		}
	return flag;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--));
}

//���Լ�¼���һ���Ѿ�������Ҫ����������Ԫ�صĺ�����Ǹ���λ�ã���Ϊ������ٺ���ľ�û���н����ˣ����Ѿ���������һ�˲��ǵ�hi-1������last-1��
template<typename T>
Rank Vector<T>::bubble2(Rank lo, Rank hi) {
	Rank last = lo;
	for (int i = lo; i < hi - 1; i++) {
		if (_elem[i] > _elem[i + 1]) {
			std::swap(_elem[i], _elem[i + 1]);
			last = i + 1;
		}
	}
	return last;
}

template<typename T>
void Vector<T>::bubbleSort2(Rank lo, Rank hi) {
	while ( lo < (hi = bubble2(lo, hi)) );
}


template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	Rank r = lo;
	while (lo < hi)
		if (_elem[lo] > _elem[r])
			r = lo;
	return r;
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi) {
	T* A = _elem + lo;
	T* B = new T[mid - lo];
	T* C = _elem + lo;
	Rank i = 0, j = 0, k = 0, lb = mid - lo, lc = hi - mid;
	for (int i = 0; i < mid - lo; i++) { B[i] = A[i]; }
	for (; (j < lb) || (k < lc);) {
		if ( (j<lb) && ((lc<=k)||(B[j] <= C[k])) ) { A[i++] = B[j++]; }
		if ( (k<lc) && ((lb<=j)||(C[k] <= B[j])) ) { A[i++] = C[k++]; }
	}
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (lo + 2 < hi)return;
	int mid = (lo + hi) >> 1;
	mergeSort(lo, mid);
	mergeSort(mid, hi);
	merge(lo, mid, hi);
}


template<typename T>
int Vector<T>::disordered() const {
	int n = 0;
	for (int i = 0; i < _size - 1; i++)
		if (_elem[i] > _elem[i + 1])n += 1;
	return n;
}


template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const {
	while (lo < hi) {
		if (_elem[lo] == e)break;
		lo++;
	}
	return lo;
}

/*���ֶ��ֲ���������ֱ������mid������������������Ч�ʣ�ͬʱ���Ϸ����������е����һ���������*/
template<typename T>
Rank static binSearch(T *s,T const &e, Rank lo, Rank hi) {
	while (lo < hi) {
		Rank mid = (lo + hi) >> 1;
		e < s[mid] ? (hi = mid) : (lo = mid + 1);//��lo����ָ������һ�����е��1��λ�ã�Ȼ�󷵻�--lo
	}
	return --lo;
}

/*ע�⣺���ﱾӦ�ж��ֲ��Һ�쳲��������ң�����쳲�����̫�鷳�ˣ�����������Ǹ��汾�Ķ��ֲ��Һ�쳲���������O(1.414logn)��*/
template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {
	return binSearch(_elem, e, lo, hi);
}


template<typename T>
T Vector<T>::remove(Rank r) {
	T val = _elem[r];
	remove(r, r + 1);
	return val;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi)return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size -= hi - lo; shrink();
	return hi - lo;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e; _size++;
	return r;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	switch (rand()%2)
	{
	case 0:
		mergeSort(lo, hi); break;
	case 1:
		bubbleSort2(lo, hi); break;
	}
}

template<typename T>
int Vector<T>::deduplicate() {
	int _oldSize = _size;
	int i = 0, j = 0;
	while (++j < _size) {
		if (find(_elem[j], 0, i + 1) == i+1)
			_elem[++i] = _elem[j];
	}
	_size = ++i;
	return _size - _oldSize;
}

template<typename T>//O(N)
int Vector<T>::uniquify() {
	int _oldSize = _size;
	int i = 0, j = 0;
	while (++j < _size) {
		if (_elem[i]!=_elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;
	shrink();
	return _size - _oldSize;
}

template<typename T>
void Vector<T>::traverse(void(*visit) (T&)) {
	int i = -1;
	while (++i < _size)
		visit(_elem[i]);
}

template<typename T>
template <typename VST> void Vector<T>::traverse(VST& visit) {
	int i = -1;
	while (++i < _size)
		visit(_elem[i]);
}

template<typename T>
Vector<T> & Vector<T>::copy(Vector<T> const&V, int lo, int high) {
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, lo, high); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template<typename T>class PQ_ComplHeap;

template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {
	PQ_ComplHeap<T> H(_elem + lo, hi - lo);
	while (!H.empty())
		_elem[--hi] = H.delMax();
}

#include <stdlib.h>

//���ﴫ���lo,hi��,hi�������ڱ�,[lo,hi]����_elem
//[lo+1,mi]��¼���Ǳ����С��,[mi+1,k-1]��¼���Ǳ������
template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
	std::swap(_elem[lo], _elem[lo + rand() % (hi + 1 - lo)]);//���ѡ�����,�����˻�����
	int mi = lo;
	for (int k = lo + 1; k <= hi; k++) {//lo�������,���Դ�lo+1��ʼѭ��
		if (_elem[k] >= _elem[lo])//����������,ʲôҲ����
			;
		else //���С�����
			std::swap(_elem[++mi], _elem[k]);
	}
	std::swap(_elem[lo], _elem[mi]);//�����ŵ��м�
	return mi;
}

template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
	if (hi - lo < 2)return;
	int mi = partition(lo, hi - 1);
	quickSort(lo, mi);
	quickSort(mi + 1, hi);
}