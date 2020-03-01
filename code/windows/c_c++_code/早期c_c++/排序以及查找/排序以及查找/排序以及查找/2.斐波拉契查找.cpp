#include<iostream>

using namespace std;

//根据黄金分割分割每个阶段
int Fibonacci_Search(int* array, int key,int elemnum)
{
	int Fibonacci[46];
	Fibonacci[0] = 1;
	Fibonacci[1] = 1;
	//构建一个50个元素的斐波那契数列
	//斐波那契数列47超过int范围
	for (int i = 2; i < 46; i++)
	{
		Fibonacci[i] = Fibonacci[i - 1] + Fibonacci[i - 2];
	}
	//如果要查找的数组最大元素>斐波那契数列中的最大元素
	if (array[elemnum - 1] > Fibonacci[45])
	{
		cout << "array max too big" << endl;
		return -1;
	}
	//当前数组元素个数对应的斐波那契数列中的元素
	int FibonacciStage = 0;
	while (elemnum > Fibonacci[FibonacciStage])
	{
		FibonacciStage++;
	}
	if (elemnum <= 0 )
	{
		exit(0);
	}
	int low = 0;
	int high = elemnum - 1;
	int mid = 0;
	for (int i = elemnum; i < Fibonacci[FibonacciStage]; i++)//补满数组元素至一个斐波那契数列值的数量
	{
		array[i] = array[high];
	}
	while (low < high)
	{
		mid = low + Fibonacci[FibonacciStage - 1];
		if (key == array[mid])
		{
			return mid;
		}
		if (key > array[mid])
		{
			low = mid + 1;
			FibonacciStage = FibonacciStage - 2;
		}
		if (key < array[mid])
		{
			high = mid - 1;
			FibonacciStage = FibonacciStage - 1;
		}
	}
	return -1;
}


void main2()
{
	int array[13] = { 1,3,7,11,17,23,29,31,37,41,43,47,53 };
	cout << Fibonacci_Search(array, 37 , 13);

	cin.get();
}