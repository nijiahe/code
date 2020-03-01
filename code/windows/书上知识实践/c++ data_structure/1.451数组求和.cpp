#include <iostream>
#include <cstdlib>

using namespace std;

int sum(int a[], int n)//共O(2n+3)
{
	int sum = 0;//O(1)
	for (int i = 0; i < n; i++)//O(n)
		sum += a[i];//O(1)
	return sum;//O(1)
}

/*分而治之法递归*/
int sum1(int a[], int lo, int hi)
{
	int mid = (lo + hi) >> 1;
	if (hi == lo)return a[lo];
	else return sum1(a, lo, mid) + sum1(a, mid + 1, hi);
}

/*减而治之法递归*/
int sum2(int a[], int lo, int hi)//每个递归体要执行一个加法，n=0时要返回一个数，因此为O(n+1)
{
	return lo == hi ? a[lo] : sum2(a, lo, hi - 1)+a[hi];
}
int sum2(int a[], int n)//改进版，每个递归体要执行一个加法，n=0时要返回一个数，因此为O(n+1)
{
	return (n < 1) ? 0 : sum2(a, n - 1) + a[n-1];
}
/*
int sum2(int a[], int n)//注意，我原来的改进版是
{
	return (n < 1) ? a[0] : sum2(a, n) + a[n];
}
这是明显错的，因为若n代表a[]里面的元素个数，a[n]就越界了
*/

void main1_45()
{
	int arr[8] = { 5,4,3,1,2,8,6,7 };
	cout << sum2(arr, 0, 7) << endl;
	cout << sum2(arr, 8) << endl;
	system("pause");
}