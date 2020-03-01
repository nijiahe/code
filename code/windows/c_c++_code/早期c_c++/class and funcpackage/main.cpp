#include<iostream>

using namespace std;

template<typename T, typename F>
T run(T t,F f)
{
	return f(t);
}


class test
{
public:
	int num;
	test(int data):num(data)
	{

	}
	int operator ()(int N)
	{
		return num*N;
	}
};

void main()
{
	cout << run(101, test(3)) << endl;/*µÈ¼ÛÓÚtest(3)(101)*/
	std::cin.get();
}