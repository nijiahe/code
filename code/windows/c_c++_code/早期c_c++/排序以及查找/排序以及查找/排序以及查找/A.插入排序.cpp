#include <iostream>

using namespace std;


//若这个数比后一个数大,找到第一个比他大的数,从这个数开始把数往后移1,将这个数插入到此位置

/*原理:
已有a[0],新来个a[1],与a[0]比较,如a[1]大,直接插入,如a[1]小,a[0]往后移1，a[1]插入a[0]处
又新来a[2],如果比a[1]大,直接插入,如果比a[1]小,在前面已排序好的顺序中找到第一个比他大的,从那个数开始全部往后移1，插入那个数的位置
又新来a[3]，同a[2],先比较a[2]和a[3],同上
……
*/
void Insert_Sort(int* array, int elemnum)
{
	for (int i = 1; i < elemnum; i++)
	{
		if (array[i - 1] > array[i])
		{
			int index = 0;
			while (array[index] <= array[i])
			{
				index++;
			}
			int temp = array[i];
			for (int j = i; j >index; j--)
			{
				array[j] = array[j - 1];
			}
			array[index] = temp;
		}
	}
}


void mainA()
{
	int array[10];
	for (int i = 0; i < 10; i++)//对数组进行随机数初始化
	{
		array[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
		cout << array[i] << " ";
	cout << endl;
	Insert_Sort(array, 10);
	for (int i = 0; i < 10; i++)
		cout << array[i] << " ";
	cin.get();
}
