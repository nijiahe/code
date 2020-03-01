#pragma once

#include "Vector.h"

//k选取算法,最坏情况O(n^2),平均性能O(n),c++数据结构书中讲的是改进为最坏情况也为O(n)的,即改变了随机选取轴点,改为选取中位数的中位数
//但视频里讲的是这个未改进版
template<typename T>
void quickSelect(Vector<T>& A, int k) {
	int lo = 0, hi = A.size() - 1;
	//[lo,hi]标记了当前寻找轴点的范围
	while (lo < hi) {
		int i = lo, j = hi;//i一开始先指向空(A[lo]是轴点,被看作空)
		T pivot = A[lo];//A[lo]作为轴点
		while (i < j) {
			while ((i < j) && (pivot<=a[j]))//如果当前j大于轴点
				j--;//将之归入
			//否则A[j]与空位互换位置
			a[i] = a[j];//此时空位被换到了A[j]处
			while ((i < j) && (pivot >= a[i]))//同理,将i处的也一个一个归入
				i++;
			a[j] = a[i];//将不满足的放到空位上
		}
		//此时i=j,减而治之,将多余的那部分去掉
		if (k < i)hi = i - 1;
		if (k > i)li + 1;
	}
	//此时lo=hi,A[k]处存的就是按顺序排列的k
}