/*Ҫ����GPU��Ҫ�����ԡ������ԡ����������������޸�*/
#include<iostream>
#include<amp.h>
/*CPU��ר�Ŵ���һ�����ݿ�*/
/*GPUͬʱ���������ݵ�ʱ���*/
using namespace std;
using namespace concurrency;/*������*/
void main10()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	array_view<int> arrayscan(10, a);/*����һ��GPU��������*//*��һ�������������鳤��,�ڶ����������������ַ*/
	parallel_for_each(arrayscan.extent, [=](index<1> idx) restrict(amp) 
	{
		arrayscan[idx] += 1; 
	});
	/*=����ֱ�Ӷ����ݸ�ֵ*/
	/*index<1>���յ���GPU����ָ�뷵�ص�����ÿ��Ԫ�ر��*/
	/*restrict(amp)������GPU�м���*/
	/*��arrayscanÿ�������Ԫ��+1*/
	for (int i = 0; i < 10; i++)
	{
		cout << arrayscan[i] << endl;
	}
	cin.get();
	return;
}