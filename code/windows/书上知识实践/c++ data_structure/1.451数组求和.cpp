#include <iostream>
#include <cstdlib>

using namespace std;

int sum(int a[], int n)//��O(2n+3)
{
	int sum = 0;//O(1)
	for (int i = 0; i < n; i++)//O(n)
		sum += a[i];//O(1)
	return sum;//O(1)
}

/*�ֶ���֮���ݹ�*/
int sum1(int a[], int lo, int hi)
{
	int mid = (lo + hi) >> 1;
	if (hi == lo)return a[lo];
	else return sum1(a, lo, mid) + sum1(a, mid + 1, hi);
}

/*������֮���ݹ�*/
int sum2(int a[], int lo, int hi)//ÿ���ݹ���Ҫִ��һ���ӷ���n=0ʱҪ����һ���������ΪO(n+1)
{
	return lo == hi ? a[lo] : sum2(a, lo, hi - 1)+a[hi];
}
int sum2(int a[], int n)//�Ľ��棬ÿ���ݹ���Ҫִ��һ���ӷ���n=0ʱҪ����һ���������ΪO(n+1)
{
	return (n < 1) ? 0 : sum2(a, n - 1) + a[n-1];
}
/*
int sum2(int a[], int n)//ע�⣬��ԭ���ĸĽ�����
{
	return (n < 1) ? a[0] : sum2(a, n) + a[n];
}
�������Դ�ģ���Ϊ��n����a[]�����Ԫ�ظ�����a[n]��Խ����
*/

void main1_45()
{
	int arr[8] = { 5,4,3,1,2,8,6,7 };
	cout << sum2(arr, 0, 7) << endl;
	cout << sum2(arr, 8) << endl;
	system("pause");
}