#include <iostream>

using namespace std;


//��������Ⱥ�һ������,�ҵ���һ�����������,���������ʼ����������1,����������뵽��λ��

/*ԭ��:
����a[0],������a[1],��a[0]�Ƚ�,��a[1]��,ֱ�Ӳ���,��a[1]С,a[0]������1��a[1]����a[0]��
������a[2],�����a[1]��,ֱ�Ӳ���,�����a[1]С,��ǰ��������õ�˳�����ҵ���һ���������,���Ǹ�����ʼȫ��������1�������Ǹ�����λ��
������a[3]��ͬa[2],�ȱȽ�a[2]��a[3],ͬ��
����
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
	for (int i = 0; i < 10; i++)//����������������ʼ��
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
