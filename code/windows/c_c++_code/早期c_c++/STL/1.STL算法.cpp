#include<iostream>
#include<algorithm>/*�㷨ͷ�ļ�*/
#include<functional>
#include<vector>
using namespace std;

class myout
{
public:
	void operator ()(int num)
	{
		cout << num << endl;
	}
};


/*for_each,������װ��*/
void main11()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	/*��*/int res = 0;
	/*for_each����������Ϊ����ָ��*/
	for_each(a, a + 9, [&res](int num) {cout << num << endl; });
	for_each(a, a + 9, myout());
	cin.get();
}
/*find*/
void main12()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = find(a, a + 9, 15);/*����find��ָ����a~a+9֮���ƶ�*/
	cout << *(a + 10) << endl;
	cout << *p << endl;
	cout << a + 10 << endl;
	cout << p << endl;
	cin.get();
}
bool ifless5(int num)
{
	return num < 5;
}
void main13()
{
	int a[10] = { 5,4,3,4,5,6,7,8,9,10 };
	/*find_if ���ص�һ��boolΪ�����*/
	/*auto ifind = find_if(a, a + 9, bind1st(greater<int>(), 2));/*find_if(�׵�ַ,ĩ��ַ,��һ������(�Ҹ�С��,3)*/
	/*�������һ���ҵ��ı�����ֵС��ֵ*/
	/*����ĵ�����������һ������,����һ��bool,�������1,�ͽ���ִ�в����ص�ǰ��ֵ,���0,�ͼ���*/
	auto ifind = find_if(a, a + 9,ifless5);
	cout << *ifind << endl;
	cin.get();
}
void main14()
{
	vector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);/*Ѱ��*/
	auto ifind = find(vec1.begin(), vec1.end(), 4);
	cout << *ifind << endl;
	cin.get();
}

bool isok(int num)
{
	return num == 5;
}
void main()
{
	vector<int> vec1;
	vec1.push_back(5);
	vec1.push_back(1);
	vec1.push_back(1);
	vec1.push_back(3);
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(0);/*����*/
	//sort(vec1.begin(), vec1.end());/*�������������Է�_Pr_Pred�����Զ����жϷ���*/
	/*fill(vec1.begin(), vec1.end(), 3);/*��ÿ��Ԫ�����Ϊ3*/
	/*fill(vec1.begin()+2, vec1.end(), 3);
	/*����vec1.begin()+2:���ԵĴ洢��ʽ������ô��,��ʽ�洢��ʽ����*/
	
	int num = count(vec1.begin(), vec1.end(), 1);/*ͳ��һ���ж��ٸ�1*/
	cout << num << endl;
	auto it=adjacent_find(vec1.begin(), vec1.end());/*���ص�һ������ͬ���ݵĽڵ������ͷ*/
	for_each(vec1.begin(), vec1.end(), [](int num) {cout << num << " "; });
	cout << endl;
	/*random_shuffle(vec1.begin(), vec1.end(),isok );/*�������������Դ�ŷֿ�ĺ���*/
	/*partition(vec1.begin(), vec1.end(), isok);/*�������򷨷���*//*�����������������Щ��������*/
	partial_sort(vec1.begin(),vec1.end()-2,vec1.end());/*ֻ��ǰ����Χ�ڴ�С��������������������*/
	//rotate(vec1.begin(), vec1.begin()+3, vec1.end());/*��������:��һ�� Ҫ��λ���׵�ַ  �ڶ���  Ҫ��λ��ĩ��ַ ������ ��λ����λ��*/
	

	for_each(vec1.begin(), vec1.end(), [](int num) {cout << num << " "; });
	cout << endl;
	cin.get();
}

void main16()
{
	int a[6] = { 2,3,1,2,5,15 };
	while (prev_permutation(a, a + 6))/*ÿ��ѭ���������е������г�һ���ȳ�ʼ����С��������,*/
	{
		cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] <<" "<<a[4]<<" " <<a[5]<< endl;
	}
	cin.get();
}