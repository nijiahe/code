#include "common.h"

#define N 5

//判断此x是否可以满足要求(利用贪心算法从n个items中选取k个)
bool OK(pair<int, int>* in_items, int n, int k,double x) {
	//升序按照v(i)-x*w(i)的大小排列
	sort(in_items, in_items + n, [x](pair<int,int> a,pair<int,int> b)->bool {
		return (a.second - x * a.first) > (b.second - x * b.first);
	});
	double sum = 0;
	//排列完成,取出前k个,计算是否满足要求
	for (int i = 0; i < k; i++)
		sum += in_items[i].second - x * in_items[i].first;
	return sum >= 0;
}

//从有n个物品的items数组中选择k个物品,使得平均值最大,返回最大平均值
double max_average(std::pair<int, int> items[],int n,int k) {
	std::pair<int, int>* in_items = new std::pair<int, int>[n];//函数内部使用的数组,因为不能更改原数组
	for (int i = 0; i < n; i++)//进行复制
		in_items[i] = items[i];
	//对数组进行排序升序排序,获取到x_max,x_min
	std::sort(in_items, in_items + n, [](std::pair<int,int> a,std::pair<int,int> b)->bool {
		return (a.second / (double)(a.first)) < (b.second / (double)(b.first));
	});
	//进行100次二分查找
	double x_max = in_items[n - 1].second/(double)(in_items[n-1].first);
	double x_min = in_items[0].second / (double)(in_items[0].first);
	double x_mid;
	for (int i = 0; i < 100; i++) {
		x_mid = (x_max + x_min) / 2;
		if (OK(in_items, n, k, x_mid))
			x_min = x_mid;
		else
			x_max = x_mid;
	}
#ifdef _DEBUG
	cout << "select such items:" << endl;
	for (int i = 0; i < k; i++)
		cout << "weight :" << in_items[i].first << ",value :" << in_items[i].second << endl;
#endif // _DEBUG

	return x_mid;
}

int main3_1_4() {
	int k = 2;//选取3个,使得平均值最大
	//pair.first表示weight,pair.second表示value
	std::pair<int, int> items[] = { {2,3},{2,1},{5,3},{2,1},{3,2} };
	// x = Σv(i)/Σw(i),则即求使得Σv(i) - Σw(i)*x>=0最大的x,所以可以对v(i)-x*w(i)进行贪心的选择

	cout << "average is " << max_average(items, N, k) << endl;

	return 0;
}