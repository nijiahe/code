#include "common.h"

//O(nk)的找零方法,使找的零钱总数最小,动态规划
/*
思考方式:用表格法记录前i-1个元素的最佳找零方案,i的最佳找零方案只不过是1+min{ i-K[j]},即假定此次找零中包含一种面值,找出去掉这个面值后的最小值
每个元素花O(k)的时间,共O(nk),空间复杂度O(n)
*/

//输入面值数组Money,数组大小s,其中必包含面值为1的硬币,以应对任何找零情况,求n的找零方式,动态规划
int change(int* Money, int s, int n) {
	int* nums = new int[n + 1];
	for (int i = 0; i <= n; i++)nums[i] = INT_MAX;//初始化
	nums[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < s; j++) {//遍历面值数组
			if (Money[j] <= i) {//可以用这个面值的硬币来分割成子问题,即当前要求找零面值比此面值大
				int n = 1 + nums[i - Money[j]];
				if (nums[i] > n)
					nums[i] = n;
			}
		}
	}

#ifdef _DEBUG
	cout << "start log nums" << endl;
	cout << setw(7) << "money";
	for (int i = 0; i <= n; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << setw(7) << "num";
	for (int i = 0; i <= n; i++)
		cout << setw(3) << nums[i];
	cout << endl;
#endif

	int val = nums[n];
	delete[]nums;
	return val;
}


int mains16_1() {
	int Money[6] = { 11,9,5,4,3,1 };
	int n = change(Money, 6, 36);

	return 0;
}