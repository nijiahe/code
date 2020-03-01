#include<iostream>

using namespace std;

//�ȸ�����λ�ý��������С��Ԫ���ŵ�ǰ��,�ڽ���΢��
/*ԭ��
0 1 2 3 4 5 6 7 8 9 
����ȡ�ϴ�ļ����Ϊ����д��µ�����,��һ��ʼȡ�����Ϊ4,���a[0],a[4],a[8]��������,����ԭ��Ϊ��������
����С�����,ͬ���ò�������
�۵��������С��1ʱ,���ò��������������������,����Ϊ֮ǰ�Ѿ����������΢��,��������������
��:�������������1
*/
void Shell_Sort(int* array, int elemnum)
{
	if (elemnum <= 0 || array == nullptr)
	{
		return;
	}
	int grade = 0;
	int rearindex;
	int adelem;
	while (elemnum > grade)
	{
		grade = 3 * grade + 1;
	}
	while (grade > 0)
	{
		for (int i = grade; i < elemnum; i++)
		{
			rearindex = i - grade;
			adelem = array[i];
			while (rearindex >= 0 && array[rearindex] > adelem)
			{
				array[rearindex + grade] = array[rearindex];
				rearindex -= grade;
			}
			array[rearindex + grade] = adelem;
		}
		grade = (grade - 1) / 3;
	}
}


void mainC()
{
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	Shell_Sort(array, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cin.get();
}