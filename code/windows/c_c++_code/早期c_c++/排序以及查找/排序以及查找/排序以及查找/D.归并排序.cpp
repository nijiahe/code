#include<iostream>

using namespace std;

//先将每个分组分为1个元素对相邻元素进行调整,然后对2个元素的分组将元素从大到小分到temp里,依次在复制到原来数组,
/*
原理:
①将一个大数组分为两个小数组,再将两个小数组分为四个,直到每个数组里的元素个数为2,后面会进行到元素个数不匹配的数组进行合并,如2个元素的和3个元素的数组
②先对元素个数为2的数组排序,然后在对更多元素的数组进行排序,即比较每个数组最开始元素的大小,记录数组walk当前位置,按照移动把每个元素复制到temp数组内
*/
class MergeSort
{
public:
	int* array;
	int elemnum;
	int* temp;
	MergeSort()
	{

	}
	MergeSort(int* array, int elemnum) :array(array), elemnum(elemnum),temp(new int[elemnum])
	{

	}
	~MergeSort()
	{
		delete[] temp;
	}
	int merge_Sort()
	{
		if (elemnum < 0 || array == nullptr)
		{
			return 0;
		}
		Sort(0, elemnum - 1);
		cout << endl;
		return 1;
	}
private:
	void Sort(int begin,int end)
	{
		if (end - begin > 1)
		{
			Sort(begin, (begin + end) / 2);
			Sort((begin + end) / 2 + 1, end);
			int i = begin;//前半部分数组目录
			int j = (begin + end) / 2 + 1;//后半部分数组目录
			int k = begin;//temp数组目录
			while (j <= end&&i <= (begin + end) / 2)//
			{
				if (array[i] > array[j])
				{
					temp[k++] = array[j++];
				}
				else
				{
					temp[k++] = array[i++];
				}
			}
			while (j <= end)
			{
				temp[k++] = array[j++];
			}
			while (i <= (begin + end) / 2)
			{
				temp[k++] = array[i++];
			}
			for (int i = begin; i <= end; i++)//如果这里不先把值赋给原有数组,原有数组相当于未经过排序,不能进行直接的大分组排序
			{
				array[i] = temp[i];
			}
		}
		else
		{
			if (array[begin] > array[end])
			{
				array[begin] = array[begin] + array[end];
				array[end] = array[begin] - array[end];
				array[begin] = array[begin] - array[end];
			}
		}
	}
};

void mainD()
{
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100;
		cout << array[i] << " ";
	}
	cout << endl;
	MergeSort sort1(array, 10);
	sort1.merge_Sort();
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	cin.get();
}