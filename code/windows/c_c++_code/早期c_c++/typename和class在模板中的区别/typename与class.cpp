#include<iostream>

using namespace std;

template<typename T>
class test
{
public:
	typename T::testtype* ptr;/*�������typename,��������� T::testtype����T����ľ�̬��Ա�������߱���(��Ϊֻ�о�̬�Ĳ��ܲ�����ʵ��ֱ�ӷ���)*/
};/*����typename�Ժ������֪��������T�ﶨ�������*/

class temp
{
public:
	int* ptr;
	typedef int testtype;
};
void main()
{
	test<temp> test1;
	cin.get();
}