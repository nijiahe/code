#include<iostream>

using namespace std;

//����Ҫ�ҵ�������ֵmid������������ı������¶�λmid��ֵ
int Interpolation_Search(int* array, int key,int elemnum)
{
	if (elemnum <= 0)
	{
		exit(0);
	}
	int low = 0;
	int high = elemnum - 1;
	while (low < high)
	{
		int mid = low + (high - low)*(key - array[low]) / (array[high] - array[low]);
		cout << "*" << endl;
		if (array[mid] == key)
		{
			return mid;
		}
		else
		{
			if (array[mid] > key)
			{
				high = mid - 1;
			}
			if (array[mid] < key)
			{
				low = mid + 1;
			}
		}
	}
	return -1;
}

void main1()
{
	int array[10] = { 1,2,3,4,5,6,7,8,9,10 };
	cout << Interpolation_Search(array, 10, 10) << endl;
	cin.get();
}