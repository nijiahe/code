#include "common.h"
#include <vector>

//��COMPARE(prev,later)����true,���ü���ǰ��
template<typename T>
void insertion_Sort(T* arr, int n,bool(*COMPARE)(T,T)) {
	if (n <= 1)//��������,ֱ�ӷ���
		return;
	for (int i = 1; i < n; i++) {
		T val = arr[i];
		int j = i - 1;
		while ((j>=0)&&!COMPARE(arr[j],val)) {//������
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