#pragma once

typedef int Rank;
#define DEFAULT_CAPACITY 2

template<typename T>
class Vector {

protected:
	Rank _size;//规模
	int _capacity;//容量
	T* _elem;//数据区

	/*内部函数*/
	void copyFrom(T const *A, Rank lo, Rank hi);//复制数组区间A[lo, hi)
	void expand();//空间不足时扩容
	void shrink();//装填因子过小时压缩
	bool bubble(Rank lo, Rank hi);//扫描交换(即冒泡排序中的一次循环)
	Rank bubble2(Rank lo, Rank hi);
	void bubbleSort2(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);//冒泡排序
public:
	Rank max(Rank lo, Rank hi);//取最大值
	void selectionSort(Rank lo, Rank hi);//选择排序
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergeSort(Rank lo, Rank hi);//归并排序算法
	void heapSort(Rank lo, Rank hi);//堆排序
	Rank partition(Rank lo, Rank hi);//轴点构造算法
	void quickSort(Rank lo, Rank hi);//快速排序算法
	void shellSort(Rank lo, Rank hi);//希尔排序算法
	int disordered() const;

public:
	/*构造函数*/
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
	{ _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v); } //s<=c
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
	/*析构函数*/
	~Vector() { delete[] _elem; }
	/*只读访问接口*/
	Rank size()const { return _size; }
	bool empty()const { return !_size; }
	Rank find(T const& e)const { return find(e, 0, _size); }
	Rank find(T const& e, Rank lo, Rank hi)const;//从[lo,hi)范围内查找
	Rank search(T const& e)const {//有序向量区间查找
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//有序向量整体查找
	/*可写访问接口*/
	T& operator[](Rank r) { return _elem[r]; }
	const T& operator[](Rank r)const { return _elem[r]; }
	Vector<T> & operator=(Vector<T>const& V) {
		if (_elem) delete[] _elem; //释放原有内容
			copyFrom(V._elem, 0, V.size()); //整体复制
		return *this; //返回当前对象的引用，以便链式赋值
	}
	T remove(Rank r);
	int remove(Rank lo, Rank hi);//删除区间[lo,hi),返回删去的长度
	Rank insert(Rank r, T const& e); //插入元素
	Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入
	void sort(Rank lo, Rank hi); //对[lo, hi)排序
	void sort() { sort(0, _size); } //整体排序
	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
	void unsort() { unsort(0, _size); } //整体置乱
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	Vector<T> & copy(Vector<T> const&V, int lo, int high);
	/*遍历接口*/
	void traverse(void(*) (T&));
	template <typename VST> void traverse(VST&);
};

#include "Vector_implementation.h"