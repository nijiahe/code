#include<iostream>

using namespace std;

int add(int num1, int num2)
{
	return num1 + num2;
}
void main01()
{
	int(*p)(int, int) = add;
	cout << p(1, 2) << endl;
	/*这两个表示的都是存储了add函数的函数指针的地址,编译器做了*/
	cout << p << endl;
	cout << *****p << endl;/*编译器自动将*p编译为p,不让用户获得函数的地址*/
	cout << &p << endl;
	cout << typeid(p).name() << endl;
	cout << typeid(***p).name() << endl;
	cout << typeid(&p).name() << endl;
	std::cin.get();
}
/*获取普通函数的地址*/

class test
{
public:
	int x;
	int y;
	test(int num1,int num2):x(num1),y(num2)
	{

	}
	int add(int num1, int num2)
	{
		return num1 + num2;
	}
	int minus(int num1, int num2)
	{
		return num1 - num2;
	}
	int multy(int num1, int num2)
	{
		return num1 * num2;
	}
	int devide(int num1, int num2)
	{
		return num1 / num2;
	}
	int show()
	{
		return x + y;
	}
};
/*获取成员函数中的地址并调用*/
void main02()
{
	test tes1(2, 3);
	int(test::*p)(int, int) = &test::add;/*创建指针指向类中的函数*/
	int(test::*ptr)() = &test::show;/*创建指针指向类中的函数*/
	cout << (tes1.*p)(3, 5) << endl;//调用类中函数必须加上类的实例,因为类中的函数可以调用类中的成员变量,不加上实例会导致函数的生命周期比变量大,
	cout << (tes1.*ptr)() << endl;
	std::cin.get();
}
typedef int(test::*P)(int, int);/*定义类型,将int(test::*)(int,int)类型函数指针定义为P*/

void main()
{
	test tes1(3, 2);
	P func[4] = { &test::add,&test::minus, &test::multy, &test::devide };/*定义一个函数指针数组,数组中的每一个元素指向类中的函数*/
	int(test::*ptr[4])(int, int)= { &test::add,&test::minus, &test::multy, &test::devide };
	for (int i = 0; i < 4; i++)/*循环依次调用加减乘除*/
	{
		cout << (tes1.*ptr[i])(9, 5) << endl;
	}
	int(test::**p)(int, int) = ptr;/*指向类成员函数指针的指针*/
	for (; p < ptr + 4; p++)
	{
		cout << (tes1.**p)(9,5) << endl;
	}
	std::cin.get();
}
