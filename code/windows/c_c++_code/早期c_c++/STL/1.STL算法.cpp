#include<iostream>
#include<algorithm>/*算法头文件*/
#include<functional>
#include<vector>
using namespace std;

class myout
{
public:
	void operator ()(int num)
	{
		cout << num << endl;
	}
};


/*for_each,函数包装器*/
void main11()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	/*①*/int res = 0;
	/*for_each第三个参数为函数指针*/
	for_each(a, a + 9, [&res](int num) {cout << num << endl; });
	for_each(a, a + 9, myout());
	cin.get();
}
/*find*/
void main12()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = find(a, a + 9, 15);/*允许find的指针在a~a+9之间移动*/
	cout << *(a + 10) << endl;
	cout << *p << endl;
	cout << a + 10 << endl;
	cout << p << endl;
	cin.get();
}
bool ifless5(int num)
{
	return num < 5;
}
void main13()
{
	int a[10] = { 5,4,3,4,5,6,7,8,9,10 };
	/*find_if 返回第一个bool为真的数*/
	/*auto ifind = find_if(a, a + 9, bind1st(greater<int>(), 2));/*find_if(首地址,末地址,绑定一个函数(找更小的,3)*/
	/*会输出第一个找到的比输入值小的值*/
	/*这里的第三个参数是一个函数,返回一个bool,如果返回1,就结束执行并返回当前数值,如果0,就继续*/
	auto ifind = find_if(a, a + 9,ifless5);
	cout << *ifind << endl;
	cin.get();
}
void main14()
{
	vector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);/*寻找*/
	auto ifind = find(vec1.begin(), vec1.end(), 4);
	cout << *ifind << endl;
	cin.get();
}

bool isok(int num)
{
	return num == 5;
}
void main()
{
	vector<int> vec1;
	vec1.push_back(5);
	vec1.push_back(1);
	vec1.push_back(1);
	vec1.push_back(3);
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(0);/*排序*/
	//sort(vec1.begin(), vec1.end());/*第三个参数可以放_Pr_Pred代表自定的判断方法*/
	/*fill(vec1.begin(), vec1.end(), 3);/*将每个元素填充为3*/
	/*fill(vec1.begin()+2, vec1.end(), 3);
	/*关于vec1.begin()+2:线性的存储方式可以这么用,链式存储方式不行*/
	
	int num = count(vec1.begin(), vec1.end(), 1);/*统计一共有多少个1*/
	cout << num << endl;
	auto it=adjacent_find(vec1.begin(), vec1.end());/*返回第一个有相同数据的节点的链表头*/
	for_each(vec1.begin(), vec1.end(), [](int num) {cout << num << " "; });
	cout << endl;
	/*random_shuffle(vec1.begin(), vec1.end(),isok );/*第三个参数可以存放分块的函数*/
	/*partition(vec1.begin(), vec1.end(), isok);/*快速排序法分区*//*第三个参数代表对哪些参数排序*/
	partial_sort(vec1.begin(),vec1.end()-2,vec1.end());/*只对前排序范围内大小的数量的数据排序排序*/
	//rotate(vec1.begin(), vec1.begin()+3, vec1.end());/*三个参数:第一个 要移位的首地址  第二个  要移位的末地址 第三个 移位到的位置*/
	

	for_each(vec1.begin(), vec1.end(), [](int num) {cout << num << " "; });
	cout << endl;
	cin.get();
}

void main16()
{
	int a[6] = { 2,3,1,2,5,15 };
	while (prev_permutation(a, a + 6))/*每次循环用数组中的数排列成一个比初始的数小的最大的数,*/
	{
		cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] <<" "<<a[4]<<" " <<a[5]<< endl;
	}
	cin.get();
}