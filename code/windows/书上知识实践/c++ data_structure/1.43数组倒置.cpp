#include <iostream>
#include <cstdlib>

using namespace std;

/*减而治之思想*/
void reverse(int a[], int lo, int hi)
{
	if (lo < hi) { swap(a[lo], a[hi]); reverse(a, lo + 1, hi - 1); }
}

void main1_43()
{
	int arr[8] = { 1,2,3,4,5,6,7,8 };
	for (auto i : arr) { cout << i << ' '; }
	cout << endl;
	reverse(arr, 0, 7);
	for (auto i : arr) { cout << i << ' '; }
	cout << endl;

	system("pause");
}