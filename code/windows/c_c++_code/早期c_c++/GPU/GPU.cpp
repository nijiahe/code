/*要调试GPU需要在属性——调试——调试器类型中修改*/
#include<iostream>
#include<amp.h>
/*CPU是专门处理一个数据快*/
/*GPU同时处理多个数据的时候快*/
using namespace std;
using namespace concurrency;/*并发性*/
void main10()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	array_view<int> arrayscan(10, a);/*创建一个GPU类型数组*//*第一个参数代表数组长度,第二个参数传入数组地址*/
	parallel_for_each(arrayscan.extent, [=](index<1> idx) restrict(amp) 
	{
		arrayscan[idx] += 1; 
	});
	/*=代表直接对数据赋值*/
	/*index<1>接收的是GPU数组指针返回的数组每个元素编号*/
	/*restrict(amp)限制在GPU中计算*/
	/*将arrayscan每个数组的元素+1*/
	for (int i = 0; i < 10; i++)
	{
		cout << arrayscan[i] << endl;
	}
	cin.get();
	return;
}