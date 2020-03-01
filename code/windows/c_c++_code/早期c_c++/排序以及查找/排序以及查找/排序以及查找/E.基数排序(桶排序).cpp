#include<iostream>

using namespace std;
/*
ԭ��:
�ٽṹ:һ��ָ������,���Լ�¼��λ����Ԫ�صľ���ֵ,
	   һ������,���Լ�¼��Ӧλ���������м���Ԫ��(����̬����)
�ڴӸ�λ����ʼ,���ո�λ���Ĵ�С���ν����ŵ���Ӧ��������
��ȫ���źú󣬰���0 1 2 3 �����ĸ�λ��С˳��ָ�������ڵ�����ֵ��ԭ������,��������ʼ����ʮλ
������ʮλʱ,���ڸ�λ�Ѿ��������,��λС���������ǰ��,����ʮλʱ���ʮλ��ͬ,��λС�Ļ��ȱ��Ž�ָ������,�����С��10����,���ʱ���մ�С�����˳�򱻷�����0��Ͱ
�������λ,���ʱС��100�������Ѿ�������˳�������0��Ͱ,����ͬ��
��ֱ�����,������û��һ�����Ĵ�С�ܳ�����ǰ��λ��,�������
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
			for (int i = 0; i < 10; i++)//�Ƚ�ͳ��ÿ��Ͱ���м���Ԫ�ص�������Ϊ0
			{
				bucketelemnum[i] = 0;
			}
			for (int i = 0; i < arrayelemnum; i++)//bucket[��ǰλ����][��ǰλ����������++]=array[i]
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
	cout << "����ǰ" << endl;
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
	cout << "�����" << endl;
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
