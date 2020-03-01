#include<iostream>

using namespace std;
/*�麯���쳣����ʵ��һ���ӿڶ���쳣����*/
template<class T>
class test
{
public:
	test(int n)
	{
		if (n > 0 && n < 10)
		{
			throw small(n);
		}
		else if (n > 10000)
		{
			throw big(n);
		}
		else if (n >= 10 && n <= 10000)
		{
			ptr = new T[n];
			size = n;
		}
		else
		{
			throw wrong(); 
		}
	}
protected:
private:
	T* ptr;
	int size;
public:
	class small:public wrong
	{
	public:
		int size;
		small(int n):size(n)
		{
			
		}
		void show()
		{
			cout << "smallwrong" << size << endl;
		}
	};
	class big:public wrong
	{
	public:
		int size;
		big(int n):size(n)
		{

		}
		void show()
		{
			cout << "bigwrong" << size << endl;
		}
	};
	class wrong
	{
	public:
		virtual void show()
		{
			cout << "wrong" << endl;
		}
	};
};


void main01()
{
	try
	{
		test<int> ts1(3);
	}
	/*�麯������ͨ������,ָ��,��ʵ�ֵ�����Ӧ��ĺ���*/
	catch (test<int>::wrong &wrong)/*wrong��show���麯��,wrong�Ǳ�Ĵ���Ļ���,��wrong�����������show����ֱ�ӵ�����Ӧ�����show*/
	{
		wrong.show();
	}
	cin.get();
}