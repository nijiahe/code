#include<iostream>
#include<amp.h>
#include<WinBase.h>

using namespace std;


double runGPU(int num)restrict(amp)/*��GPU��һ��������������*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}

double runCPU(int num)restrict(cpu)/*��CPU��һ��������������*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}
double runGPUCPU(int num)restrict(amp,cpu)/*��GPU��CPU��һ��������������*/
{
	double temp = 0;
	for (int i = 0; i < num; i++)
	{
		temp += i;
	}
	return temp;
}
/*��ͬһ�������ظ�����ʱGPU��CPU�ıȽ�*/
int main20()
{
	LARGE_INTEGER freq;/*LARGE_INTEGER��ʾһ��64λ�з�������*/
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;/*�����������͵ı��������洢ʱ��*/

	QueryPerformanceFrequency(&freq);/*ʱ�任���׼*/
	QueryPerformanceCounter(&strt);/*��¼���Կ�ʼǰ��ʱ��*/
	/*LowPart��32λ��HighPart��32λ��QuadPart�з��ŵ�64λ����*/
	/*LARGE_INTEGER�ṹʵ������һ�����ϡ������ı�������������֧��64λ������ʹ��QuadPart��Ա�д洢��64λ����������ʹ��LowPart��HighPart��Ա�Ĵ洢��64λ����*/
	cout << "freq�е�����" << freq.HighPart<<" " <<freq.LowPart<< " "<<freq.QuadPart<<endl;
	cout << "strt�е�����" << strt.HighPart << " " << strt.LowPart << " " << strt.QuadPart << endl;

	double dx[1] = { 0.0 };/*����һ������*/
	double db = 0.0;
	concurrency::array_view<double> myview(1, dx);/*�����������GPU��������*/

	concurrency::parallel_for_each(myview.extent, [=](concurrency::index<1> idx) restrict(amp)/*�������������GPU������*/
	{
		myview[idx] = runGPU(1000000);/*�����������20000��*/
	});/*myview.extent����GPU����ĵ�����*/

	/*��ʽ�ȴ�GPU������ɲ������ݴ���ڴ�*/
	cout << "ͬ����CPUǰ��dx[0]������"<<dx[0] << endl;
	myview.synchronize();/*ʹGPU�еļ�����ͬ����CPU��*/
	printf("ͬ����CPU���dx[0]������%f\n", dx[0]);

	/*GPUʱ���ʱ*/
	QueryPerformanceCounter(&ed);/*��¼GPU��������ʱ��*/
	cout << "ed�е�����" << ed.HighPart << " " << ed.LowPart << " " << ed.QuadPart << endl;
	printf("GPU�ĺ�ʱ:%d����\n", (ed.QuadPart-strt.QuadPart)*1000/freq.QuadPart);

	QueryPerformanceCounter(&strt);/*���¼�¼��ʼʱ��*/

	printf("CPU�м�����%d\n", runCPU(1000000));
	/*CPUʱ���ʱ*/
	QueryPerformanceCounter(&ed);
	printf("CPU�ĺ�ʱ:%f����\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	puts("���Խ���");
	cin.get();
	return 0;
}


#define COUNT 1000000

float nickName_GPU[COUNT];
float nickName_CPU[COUNT];

/*�����ܶ�����ʱGPU��CPU�ıȽ�*/
void main21()
{
	LARGE_INTEGER freq;
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&strt);
	concurrency::array_view<float> myView(COUNT, nickName_GPU);
	concurrency::parallel_for_each(myView.extent, [=](concurrency::index<1> idx)restrict(amp)/*��������GPU������*/
	{

		for (int i = 0; i < COUNT / 10; i++)
		{
			myView[idx] = (myView[idx] + 0.1f) / 2.3f;
		}
	});
	myView.synchronize();/*��GPU�е�����ͬ�����ڴ�*/
	QueryPerformanceCounter(&ed);/*��¼��ǰʱ��*/
	printf("GPU��ʱ:%d\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);

	QueryPerformanceCounter(&strt);
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT / 10; j++)
		{
			nickName_CPU[i] = (nickName_CPU[i] + 0.1f) / 2.3f;
		}
	}
	QueryPerformanceCounter(&ed);
	printf("CPU��ʱ:%d\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	cin.get();
}