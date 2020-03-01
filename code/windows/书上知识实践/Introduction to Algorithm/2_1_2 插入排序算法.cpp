#include "common.h"
#include <vector>

//若COMPARE(prev,later)返回true,则不用继续前移
template<typename T>
void insertion_Sort(T* arr, int n,bool(*COMPARE)(T,T)) {
	if (n <= 1)//不用排序,直接返回
		return;
	for (int i = 1; i < n; i++) {
		T val = arr[i];
		int j = i - 1;
		while ((j>=0)&&!COMPARE(arr[j],val)) {//不满足
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = val;
	}
}

bool test(int, int) {
	return true;
}

int main2_1_2() {
	vector<int> arr;
	for (int i = 0; i < 10; i++) {
		arr.push_back(rand() % 100);
	}
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	insertion_Sort<int>(&arr[0], arr.size(), [](int prev,int next)->bool {
		return prev < next;
	});
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	insertion_Sort<int>(&arr[0], arr.size(), [](int prev, int next)->bool {
		return prev > next;
	});
	for_each(arr.begin(), arr.end(), [](int i) {
		std::cout << i << " ";
	});
	cout << endl;

	return 0;
}