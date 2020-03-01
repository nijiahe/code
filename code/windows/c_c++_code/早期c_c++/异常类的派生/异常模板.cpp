#include<iostream>

using namespace std;
/*虚函数异常可以实现一个接口多个异常处理*/
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
	/*虚函数可以通过引用,指针,来实现调用相应类的函数*/
	catch (test<int>::wrong &wrong)/*wrong的show是虚函数,wrong是别的错误的基类,用wrong接收子类调用show可以直接调用相应子类的show*/
	{
		wrong.show();
	}
	cin.get();
}