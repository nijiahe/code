#include<iostream>
#include<amp.h>
#include<WinBase.h>

using namespace std;


double runGPU(int num)restrict(amp)/*用GPU对一个数据连续操作*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}

double runCPU(int num)restrict(cpu)/*用CPU对一个数据连续操作*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}
double runGPUCPU(int num)restrict(amp,cpu)/*用GPU、CPU对一个数据连续操作*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}
/*对同一个数据重复操作时GPU和CPU的比较*/
int main20()
{
	LARGE_INTEGER freq;/*LARGE_INTEGER表示一个64位有符号整数*/
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;/*创建这种类型的变量用来存储时间*/

	QueryPerformanceFrequency(&freq);/*时间换算标准*/
	QueryPerformanceCounter(&strt);/*记录测试开始前的时间*/
	/*LowPart低32位。HighPart高32位。QuadPart有符号的64位整数*/
	/*LARGE_INTEGER结构实际上是一个联合。如果你的编译器具有内置支持64位整数，使用QuadPart成员中存储的64位整数。否则，使用LowPart和HighPart成员的存储的64位整数*/
	cout << "freq中的数据" << freq.HighPart<<" " <<freq.LowPart<< " "<<freq.QuadPart<<endl;
	cout << "strt中的数据" << strt.HighPart << " " << strt.LowPart << " " << strt.QuadPart << endl;

	double dx[1] = { 0.0 };/*创建一个数组*/
	double db = 0.0;
	concurrency::array_view<double> myview(1, dx);/*将这个数组变成GPU类型数组*/

	concurrency::parallel_for_each(myview.extent, [=](concurrency::index<1> idx) restrict(amp)/*限制这个函数在GPU中运行*/
	{
		myview[idx] = runGPU(1000000);/*让这个数自增20000次*/
	});/*myview.extent类似GPU数组的迭代器*/

	/*显式等待GPU计算完成并将数据打回内存*/
	cout << "同步到CPU前的dx[0]的数据"<<dx[0] << endl;
	myview.synchronize();/*使GPU中的计算结果同步到CPU中*/
	printf("同步到CPU后的dx[0]的数据%f\n", dx[0]);

	/*GPU时间计时*/
	QueryPerformanceCounter(&ed);/*记录GPU运算完后的时间*/
	cout << "ed中的数据" << ed.HighPart << " " << ed.LowPart << " " << ed.QuadPart << endl;
	printf("GPU的耗时:%d毫秒\n", (ed.QuadPart-strt.QuadPart)*1000/freq.QuadPart);

	QueryPerformanceCounter(&strt);/*重新记录开始时间*/

	printf("CPU中计算结果%d\n", runCPU(1000000));
	/*CPU时间计时*/
	QueryPerformanceCounter(&ed);
	printf("CPU的耗时:%f毫秒\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	puts("测试结束");
	cin.get();
	return 0;
}


#define COUNT 1000000

float nickName_GPU[COUNT];
float nickName_CPU[COUNT];

/*操作很多数据时GPU和CPU的比较*/
void main21()
{
	LARGE_INTEGER freq;
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&strt);
	concurrency::array_view<float> myView(COUNT, nickName_GPU);
	concurrency::parallel_for_each(myView.extent, [=](concurrency::index<1> idx)restrict(amp)/*限制其在GPU中运行*/
	{

		for (int i = 0; i < COUNT / 10; i++)
		{
			myView[idx] = (myView[idx] + 0.1f) / 2.3f;
		}
	});
	myView.synchronize();/*将GPU中的数据同步到内存*/
	QueryPerformanceCounter(&ed);/*记录当前时间*/
	printf("GPU耗时:%d\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);

	QueryPerformanceCounter(&strt);
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT / 10; j++)
		{
			nickName_CPU[i] = (nickName_CPU[i] + 0.1f) / 2.3f;
		}
	}
	QueryPerformanceCounter(&ed);
	printf("CPU耗时:%d\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	cin.get();
}