#include "common.h"
#include <vector>

template<typename T>
T findCrossMaxArray(T* _elem, int lo, int mid, int hi, int& cross_lo, int& cross_hi) {
	T prev_max_sum = 0, next_max_sum = 0;
	T prev_s = 0, next_s = 0;
	cross_lo = cross_hi = mid;//初始化
	//[lo,mid)
	for (int i = mid - 1; i >= lo; i--) {
		prev_s += _elem[i];
		if (prev_s > prev_max_sum) {
			cross_lo = i; prev_max_sum = prev_s;
		}
	}
	//[mid,hi)
	for (int i = mid; i < hi; i++) {
		next_s += _elem[i];
		if (next_s > next_max_sum) {
			cross_hi = i + 1; next_max_sum = next_s;
		}
	}
	return prev_max_sum + next_max_sum;
}

//Find max subArray from [lo,hi),pos1、pos2 is in order to record maxArray's position[sub_lo,sub_hi)
template<typename T>
T findMaxSubArray(T* _elem, int lo, int hi,int &sub_lo,int &sub_hi) {
	sub_lo = sub_hi = lo;
	if (hi - lo < 1) {
		sub_lo = lo; sub_hi = hi;
		return 0;
	}
	if ((hi - lo == 1)) {
		if (_elem[lo] > 0) {
			sub_lo = lo; sub_hi = hi;
			return _elem[lo];
		}
		else
			return 0;
	}
	int prev_lo, prev_hi, cross_lo, cross_hi, next_lo, next_hi;
	int mid = (lo + hi) / 2;
	int prev_max = findMaxSubArray(_elem, lo, mid, prev_lo, prev_hi);
	int cross_max = findCrossMaxArray(_elem, lo, mid, hi, cross_lo, cross_hi);
	int next_max = findMaxSubArray(_elem, mid, hi, next_lo, next_hi);
	//从三者中取最大的
	if ((prev_max >= cross_max) && (prev_max >= next_max)) {
		sub_lo = prev_lo; sub_hi = prev_hi; return prev_max;
	}
	else if ((cross_max >= prev_max) && (cross_max >= next_max)) {
		sub_lo = cross_lo; sub_hi = cross_hi; return cross_max;
	}
	else {
		sub_lo = next_lo; sub_hi = next_hi; return next_max;
	}
}

//动态规划,迭代法,O(n),[sub_lo,sub_hi)
template<typename T>
T iterate_findMaxSubArray(T* _elem,int n,int& sub_lo,int& sub_hi) {
	int max_sum = 0;
	sub_lo = 0; sub_hi = 0;
	int sum_lo = 0, sum_hi = 0;
	int sum = 0;//记录当前最大值的向后延伸
	for (int i = 0; i < n; i++) {
		sum += _elem[i];
		if (sum <= 0) {//如果小于零.则最大子数组只可能是前面那个或者在后面,重新开始计数
			sum_lo = i + 1;
			sum_hi = i + 1;
			sum = 0;
		}
		else
			sum_hi++;
		if (sum > max_sum) {
			sub_lo = sum_lo;
			sub_hi = sum_hi;
			max_sum = sum;
		}
	}
	return max_sum;
}

int main4_1() {
	vector<int> arr;
	for (int i = 0; i < 10; i++) {
		arr.push_back(rand() % 20*(rand()%2?1:-1));
	}
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	//O(nlgn)的分而治之递归法
	cout << "recursive:" << endl;
	int sub_lo, sub_hi;
	int n = findMaxSubArray(&arr[0], 0, arr.size(), sub_lo, sub_hi);
	cout << "The max sum is " << n << ",and is from " << sub_lo << " to " << sub_hi << endl;
	for (int i = sub_lo; i < sub_hi; i++)
		cout << arr[i] << " ";
	cout << endl;

	//O(b)的动态规划迭代法
	cout << "iterative:" << endl;
	n = iterate_findMaxSubArray(&arr[0], arr.size(), sub_lo, sub_hi);
	cout << "The max sum is " << n << ",and is from " << sub_lo << " to " << sub_hi << endl;
	for (int i = sub_lo; i < sub_hi; i++)
		cout << arr[i] << " ";
	cout << endl;

	
	return 0;
}