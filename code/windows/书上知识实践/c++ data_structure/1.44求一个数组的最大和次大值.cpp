#include <iostream>
#include <cstdlib>

using namespace std;

/*迭代法思想1*//*注意:for语句执行前会先判断是否满足中间条件，如果不满足，一次都不会执行*///共O(2n-3)
/*
先扫描一遍选出最大的x1坐标，再以x1为分界对两边查找出次大x2坐标
*/
void Max2_1(int a[], int lo, int hi,int &x1,int &x2)
{
	x1 = lo;
	for (int i = lo + 1 ; i < hi; i++)//O(n-1)
		if (a[i] > a[x1])x1 = i;
	x2 = lo;
	for (int i = lo + 1 ; i < x1; i++)//后面两个循环的比较操作是O(n-2)
		if (a[i] > a[x2])x2 = i;
	for (int i = x1 + 1; i < hi; i++)
		if (a[i] > a[x2])x2 = i;
		
}

/*迭代法思想2*///最好的情况，即后面的O(1)永远不执行，则总体为O(n-2+1=n-1),若最差的情况，则为O(2n-4+1=2n-3)
void Max2_2(int a[], int lo, int hi, int &x1, int &x2)
{
	a[lo] > a[lo + 1] ? (x1 = lo, x2 = lo + 1) : (x1 = lo + 1, x2 = lo);//O(1)
	for(int i=lo+2;i<hi;i++)//O(n-2)
		if (a[i] > a[x2]) {//O(1)
			x2 = i;
			if (a[x2] > a[x1])//O(1)
				swap(x2, x1);
		}
}

/*分而治之递归算法*/
void Max2_3(int a[], int lo, int hi, int &x1, int &x2)
{
	if (hi == lo + 1) {
		x1 = a[lo]; x2 = a[lo]; return;
	}
	if (hi == lo + 2) {
		a[lo] > a[lo + 1] ? (x1 = lo, x2 = lo + 1) : (x1 = lo + 1, x2 = lo); return;
	}
	int xL1, xL2, xR1, xR2;
	int mid = (lo + hi) >> 1;
	Max2_3(a, lo, mid, xL1, xL2);
	Max2_3(a, mid, hi, xR1, xR2);
	if (a[xL1] > a[xR1]) {
		x1 = xL1;
		x2 = (a[xL2] > a[xR1]) ? xL2 : xR1;
	}
	else{
		x1 = xR1;
		x2 = (a[xR2] > a[xL1]) ? xR2 : xL1;
	}	
}

int main1_44()
{
	int arr[14] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	//int arr[8] = { 8,7,6,5,4,3,2,1 };
	int x1, x2;
	Max2_3(arr, 0, 14, x1, x2);
	cout << "Max = " << arr[x1] << ' ' << "Max2 = " << arr[x2] << endl;


	system("pause");
	return 0;
}