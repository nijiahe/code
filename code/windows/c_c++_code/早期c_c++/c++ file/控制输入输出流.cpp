#include<iostream>
#include<iomanip>/*�������������ͷ�ļ�*/
using namespace std;

void main01()
{

	cout.put('A').put('b')<<endl;/*��������ֽ�*/
	char str[] = "1235678946312aaaa";
	cout.write(str, 10);/*����ַ���*/
	cin.get();
}
/*���ý���*/
void main02()
{
	int num = 10;
	cout << num << endl;/*Ĭ��ʮ����*/
	cout << hex;/*ʮ������*/
	cout << num << endl;
	cout << oct;/*�˽���*/
	cout << num << endl;
	cout << dec;/*ʮ����*/
	cout << num;

	cin.get();
}
/*������Чλ��*/
void main03()
{
	double db = 1243.21212121212;/*Ĭ�ϱ���6λ��Ч����*/
	/*cout << setprecision(15);/*������ౣ�漸λ��Ч����*/
	cout << db << endl;
	cin.get();
}
/*�������*/
void main04()
{
	cout.width(10);/*�����ܿ��40*/
	/*������ʽ*/
	cout.fill('*');
	/*���õ���һ�����ʱ����ʽ*/
	cout << "hello";
	cout.setf(ios::right);/*��������Ҷ���*/
	cout.width(5);
	cout.fill('*');
	cout << " ";
	
	cout.fill('*');
	cin.get();

}
void main05()
{
	int a;
	cin.setf(ios::hex, ios::basefield);/*����cin�������ʽ(���ý���,�޸Ĵ������)*/
	cin >> a;
	cout << oct;/*������һ�������ʽ�˽���*/
	cout << a;
	cin.get();
	cin.get();
}
void main06()
{
	double db = 1000 / 7.0;/*doubleĬ�ϱ���6��С��λ��*/
	cout.setf(ios::fixed | ios::showpoint);/*����С����,��ʾС����*/
	for (int i = 0; i <10 ; i++)
	{
		cout.precision(i);/*����С����λ��*/
		cout << db << endl;
	}
	cout << db << endl;
	cout.setf(ios::scientific,ios::fixed | ios::showpoint);/*�ÿ�ѧ������*/
	/*�Զ�ѡ��С����ָ��*/
	cout << db << endl;
	cin.get();
	cin.get();
}

void main07()
{
	const int num = 1234;
	cout << setw(10) << setfill('*') << setiosflags(ios::left) << num<<endl;
	cout << setw(10) << setfill('*') << setiosflags(ios::right) << num<<endl;
	cout << resetiosflags(ios::right)<<setw(10) << setbase(8) << setfill('*') << setiosflags(ios::left) << num << endl;
	/*��ʾ��<<�����ʷ����������Ϊ�Ҷ���<<�����ܿ��10<<�����������8<<�������ַ�'*'<<���������<<���num<<*/
	cin.get();
	cin.get();
}