#pragma once

typedef int Rank;
#define DEFAULT_CAPACITY 2

template<typename T>
class Vector {

protected:
	Rank _size;//��ģ
	int _capacity;//����
	T* _elem;//������

	/*�ڲ�����*/
	void copyFrom(T const *A, Rank lo, Rank hi);//������������A[lo, hi)
	void expand();//�ռ䲻��ʱ����
	void shrink();//װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi);//ɨ�轻��(��ð�������е�һ��ѭ��)
	Rank bubble2(Rank lo, Rank hi);
	void bubbleSort2(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);//ð������
public:
	Rank max(Rank lo, Rank hi);//ȡ���ֵ
	void selectionSort(Rank lo, Rank hi);//ѡ������
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);//�鲢�����㷨
	void heapSort(Rank lo, Rank hi);//������
	Rank partition(Rank lo, Rank hi);//��㹹���㷨
	void quickSort(Rank lo, Rank hi);//���������㷨
	void shellSort(Rank lo, Rank hi);//ϣ�������㷨
	int disordered() const;

public:
	/*���캯��*/
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{ _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v); } //s<=c
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
	/*��������*/
	~Vector() { delete[] _elem; }
	/*ֻ�����ʽӿ�*/
	Rank size()const { return _size; }
	bool empty()const { return !_size; }
	Rank find(T const& e)const { return find(e, 0, _size); }
	Rank find(T const& e, Rank lo, Rank hi)const;//��[lo,hi)��Χ�ڲ���
	Rank search(T const& e)const {//���������������
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//���������������
	/*��д���ʽӿ�*/
	T& operator[](Rank r) { return _elem[r]; }
	const T& operator[](Rank r)const { return _elem[r]; }
	Vector<T> & operator=(Vector<T>const& V) {
		if (_elem) delete[] _elem; //�ͷ�ԭ������
			copyFrom(V._elem, 0, V.size()); //���帴��
		return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
	}
	T remove(Rank r);
	int remove(Rank lo, Rank hi);//ɾ������[lo,hi),����ɾȥ�ĳ���
	Rank insert(Rank r, T const& e); //����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	void unsort() { unsort(0, _size); } //��������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	Vector<T> & copy(Vector<T> const&V, int lo, int high);
	/*�����ӿ�*/
	void traverse(void(*) (T&));
	template <typename VST> void traverse(VST&);
};

#include "Vector_implementation.h"