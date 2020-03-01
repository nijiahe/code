#include<boost/bind.hpp>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>//������װ��

using namespace std;
using namespace boost;
//�̳ж����ƺ������һЩ����
class add1:public binary_function<int,int,void>//����1,����2������ֵ
{
public:
	void operator()(int i,int j) const
	{
		cout << i + j << endl;
	}

};
/*��*/
/*ʹ��c++�Դ���bind*/
/*��ֵ10��������V��ÿ��Ԫ��֮��,��ʹ�ñ�׼�������ʾ���
add()����ת��Ϊһ��������std::binary_function�ĺ�������*/
void mainB()
{
	vector<int> myvec;
	myvec.push_back(11);
	myvec.push_back(22);
	myvec.push_back(33);
	//bind1st��������һ��Ĭ�ϲ���
	for_each(myvec.begin(), myvec.end(), bind1st(add1(),10));
	cin.get();
}

/*��*/
/*ʹ��boost���е�bind*/
/*����ҪΪ��ʹ��for_each�����ĺ�����������ת��Ϊ����,
add()������Ҫ��������,��һ������Ϊ10,�ڶ���������for_each�����ֵ,��bind����ռλ��ռλ*/
void add(int i, int j)
{
	cout << i<<" " << j << " " << endl;
	cout << i + j << endl;
}

void mainC()
{
	vector<int> myvec;
	myvec.push_back(11);
	myvec.push_back(22);
	myvec.push_back(33);
	//bind(������ַ,Ĭ��ֵ,ռһ��Ĭ��λ)
	for_each(myvec.begin(), myvec.end(),bind(add, 10,_1));
	cin.get();
}