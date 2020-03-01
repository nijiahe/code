#include <iostream>
#include <string.h>
#include<array>
using namespace std;
/*定义一个类来存放错误的信息*/
/*C++通过传递类或者类的对象来传递错误信息*/
class devwrong 
{

};
/*被除数为0会引发异常*/
int intdiv(int a, int b)
{
	try
	{
		if (b == 0)
		{/*抛出一个任意类型,如也可以throw 10*/
			throw devwrong();/*抛出devwrong到错误*/
			/*抛出后会直接结束try后面的语句*/
			/*devwrong调用默认构造函数,返回一个对象*/
			cout << "aa" << endl;
		}
		return a / b;
	}
	/*catch()捕获一个对象类型*/
	catch (devwrong)/*如果错误里有devwrong*/
	{
		cout << "异常,除数为0" << endl;
		return -1;
	}
	
}
void main00()
{
	cout << intdiv(2, 0) << endl;
	cin.get();
}
/*数组溢出错误*/
class arraywrong
{

};

template<class T,int NUM>
T showarray(array<T,NUM> valuear,int num)
{
	try
	{
		if (NUM < num)
		{
			throw 10;//arraywrong();
		}
		return valuear[num];
	}
	catch (int)
	{
		cout << "查询的数据溢出数组,将返回数组最后一个元素" << endl;
		return valuear[NUM-1];
	}

}

void main()
{
	array<int,10> ar1 = { 0,1,2,3,4,5,6,7,8,9 };
	cout << showarray<int, 10>(ar1,12);

	cin.get();
}




















/*


//标识错误的类型
class wrong  
{


};

int intdiv(int a, int b)
{

	try
	{
	  
		if (b==0)
		{
			throw 10;//可以是任何对象  wrong();
		}
		int c = a / b;
		return c;


	}
	catch (int data )//类型名
	{
		
		cout << "除法异常已经处理";
		return -1;

	}


}

int intdivA(int a, int b)
{

	return a / b;
}

void main01()
{

	int x, y;
	cin >> x >> y;
	try
	{
		if (y==0)
		{
			throw "被除数为0";
		}
		else if (x==0)
		{
			throw "除数为0";
		}

	}
	catch (const char * s)
	{
		if (strcmp(s,"被除数为0")==0)
		{
			cout << "被除数为0异常，请重新输入";
			cin >> x >> y;

		}
		else  if (strcmp(s, "除数为0") == 0)
		{
			cout << "除数为0异常，请重新输入";
			cin >> x >> y;
		}

	}






	std::cout << intdiv(x, y);
	cin.get();
	cin.get();
	cin.get();







}*/