#include<iostream>

using namespace std;
/*
原理:
①结构:一个指针数组,用以记录此位数的元素的具体值,
	   一个数组,用以记录相应位数的数组有几个元素(即动态数组)
②从个位数开始,按照个位数的大小依次将数放到对应的数组内
③全部放好后，按照0 1 2 3 ……的个位大小顺序将指针数组内的数赋值到原有数组,接下来开始排序十位
④排序十位时,由于个位已经被排序过,个位小的在数组的前方,排序十位时如果十位相同,个位小的会先被放进指针数组,如果有小于10的数,则此时按照从小到大的顺序被放入了0号桶
⑤排序百位,则此时小于100的数都已经被按照顺序放入了0号桶,其他同上
⑥直到最后,数组中没有一个数的大小能超过当前的位数,排序结束
*/
class RadixSort
{
public:
	int* bucket[10];
	int bucketelemnum[10];
	int arrayelemnum;
	RadixSort(int arrayelemnum):arrayelemnum(arrayelemnum)
	{
		for (int i = 0; i < 10; i++)
		{
			bucket[i] = new int[arrayelemnum];
		}
	}
	~RadixSort()
	{
		for (int i = 0; i < 10; i++)
		{
			delete[]bucket[i];
		}
	}
	void StartSort(int* array)
	{
		int digit = 1;
		while (existbig_than(array, digit))
		{
			for (int i = 0; i < 10; i++)//先将统计每个桶里有几个元素的数组设为0
			{
				bucketelemnum[i] = 0;
			}
			for (int i = 0; i < arrayelemnum; i++)//bucket[当前位的数][当前位的数的数量++]=array[i]
			{
				bucket[array[i] / digit % 10][bucketelemnum[array[i] / digit % 10]++] = array[i];
			}
			int arrayindex = 0;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < bucketelemnum[i]; j++)
				{
					array[arrayindex] = bucket[i][j];
					arrayindex++;
				}
			}
			digit *= 10;

		}
	}
private:
	bool existbig_than(int* array, int num)
	{
		for (int i = 0; i < arrayelemnum; i++)
		{
			if (array[i] >= num)
			{
				return 1;
			}
		}
		return 0;
	}
};

void main()
{
	int array[100];
	for (int i = 0; i < 100; ++i)
	{
		array[i] = rand();
	}
	cout << "排序前" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << array[i] << " ";
		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
	RadixSort sort1(100);
	sort1.StartSort(array);
	cout << "排序后" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << array[i] << " ";
		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
	cin.get();
}
