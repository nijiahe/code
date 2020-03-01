#include<iostream>

using namespace std;

//�Ƚ�ÿ�������Ϊ1��Ԫ�ض�����Ԫ�ؽ��е���,Ȼ���2��Ԫ�صķ��齫Ԫ�شӴ�С�ֵ�temp��,�����ڸ��Ƶ�ԭ������,
/*
ԭ��:
�ٽ�һ���������Ϊ����С����,�ٽ�����С�����Ϊ�ĸ�,ֱ��ÿ���������Ԫ�ظ���Ϊ2,�������е�Ԫ�ظ�����ƥ���������кϲ�,��2��Ԫ�صĺ�3��Ԫ�ص�����
���ȶ�Ԫ�ظ���Ϊ2����������,Ȼ���ڶԸ���Ԫ�ص������������,���Ƚ�ÿ�������ʼԪ�صĴ�С,��¼����walk��ǰλ��,�����ƶ���ÿ��Ԫ�ظ��Ƶ�temp������
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
			int i = begin;//ǰ�벿������Ŀ¼
			int j = (begin + end) / 2 + 1;//��벿������Ŀ¼
			int k = begin;//temp����Ŀ¼
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
			for (int i = begin; i <= end; i++)//������ﲻ�Ȱ�ֵ����ԭ������,ԭ�������൱��δ��������,���ܽ���ֱ�ӵĴ��������
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