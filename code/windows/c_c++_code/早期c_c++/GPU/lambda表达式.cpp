#include<iostream>
#include<vector>
#include<algorithm>/*算法头文件里有for_each*/
#include<functional>
using namespace std;

void main00()
{
	vector<int> vec1;
	vec1.push_back(12);
	vec1.push_back(13);
	vec1.push_back(14);
	vec1.push_back(19);
	vector<int>::iterator ibegin, iend;
	ibegin = vec1.begin();
	iend = vec1.end();
	/*[]中放需要被返回值赋值的数据的地址*/
	for_each(ibegin, iend, [](int &num) {num *= 2; });/*lambda表达式——匿名函数*/
	for_each(ibegin, iend, [](int num) {cout << num << endl; });
	std::cin.get();
}
/*[]内为捕获列表
[=]获得函数体外部能获得的所有局部函数的const只读形式
[&]获得函数体外部能获得的所有局部函数的可读可写模式
[a]获得a的可读
[&a]是获得可读可写权限
类中的[this]获得类的读写权限*/
int main01()
{
	vector<int> vec1;
	vec1.push_back(12);
	vec1.push_back(13);
	vec1.push_back(14);
	vec1.push_back(19);
	int a = 10;
	int b = 2;
	for_each(vec1.begin(), vec1.end(), [&a](int &v) {a = 3; v += a;  cout << v << endl; });/*修改*/
	//for_each(vec1.begin(), vec1.end(), [=](int &v) {a = 3; v += a;  cout << v << endl; });/*修改*/
	/*用=捕捉只能获取只读权限*/
	/*获取可读可写权限用[&]*/
	for_each(vec1.begin(), vec1.end(), [&a](int v) {cout << v << endl; });/*遍历*/
	std::cin.get();
	return 0;
}
/*匿名函数()直接调用*/
int main02()
{
	[]() {cout << "haha" << endl; }();
	std::cin.get();
	return 0;
}

class test
{
public:
	vector<int>  myv;
	int num;
public:
	test()
	{
		num = 12;
		myv.push_back(10);
		myv.push_back(11);
	}
	void add()
	{

		//[]引用this
		int  x = 3;
		
		auto fun1 = [this, x](int v) {this->num = 3; cout << v + x + this->num << endl; };
		//=按照副本引用this，还有当前块语句局部变量，不可以赋值，但是可以读取
		//&按照引用的方式操作局部变量，this,可以赋值，可以读取
		//副本引用a,[=]   [a]
		//引用 a [&]  [&a]
		//auto fun1 = [&](int v) { cout << v + x + this->num << endl; x = 3; };
		for_each(this->myv.begin(), this->myv.end(), fun1);
	}
};

int main03()
{
	test test1;
	test1.add();
	cin.get();
	return 0;
}
/*lambda表达式返回值表示方式*/
void main04()
{
	/*①*//*已知返回类型*/
	auto minus = [](double num1, double num2)->double {return num1 / num2; };
	/*②*//*位置返回类型*/
	auto multiminus = [](int num1, double num2)->decltype(num1 / num2) { return num1 / num2; };
	cout << minus(5,6) << endl;
	cout << multiminus(2, 3) << endl;
	cout << endl;
	cin.get();
}
/*multable关键字实现获得副本的可读权限
但不能修改原本的*/
void main()
{
	int num = 10;
	auto show = [num]()mutable {num = 5; cout << "函数内部num:" << num << endl; };
	show();
	cout << "函数外部num:" << num << endl;
	cin.get();
}

//可以看到，Lambda主要分为五个部分：
//[函数对象参数]、(操作符重载函数参数)、mutable或exception声明、->返回值类型、{ 函数体 }。下面分别进行介绍。
//一、[函数对象参数]，标识一个Lambda的开始，这部分必须存在，不能省略。函数对象参数是传递给编译器自动生成的函数对象类的构造函数的。
//函数对象参数只能使用那些到定义Lambda为止时Lambda所在作用范围内可见的局部变量（包括Lambda所在类的this）。函数对象参数有以下形式：
//1、空。没有使用任何函数对象参数。
//2、 = 。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是值传递方式（相当于编译器自动为我们按值传递了所有局部变量）。
//3、&。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是引用传递方式（相当于编译器自动为我们按引用传递了所有局部变量）。
//4、this。函数体内可以使用Lambda所在类中的成员变量。
//5、a。将a按值进行传递。按值进行传递时，函数体内不能修改传递进来的a的拷贝，因为默认情况下函数是const的。要修改传递进来的a的拷贝，可以添加mutable修饰符。
//6、&a。将a按引用进行传递。
//7、a, &b。将a按值进行传递，b按引用进行传递。
//8、 = ，&a, &b。除a和b按引用进行传递外，其他参数都按值进行传递。
//9、&, a, b。除a和b按值进行传递外，其他参数都按引用进行传递。
//二、(操作符重载函数参数)，标识重载的()操作符的参数，没有参数时，这部分可以省略。参数可以通过按值（如：(a, b)）和按引用（如：(&a, &b)）两种方式进行传递。
//三、mutable或exception声明，这部分可以省略。按值传递函数对象参数时，加上mutable修饰符后，可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）。
//exception声明用于指定函数抛出的异常，如抛出整数类型的异常，可以使用throw(int)。
//四、->返回值类型，标识函数返回值的类型，当返回值为void，或者函数体中只有一处return的地方（此时编译器可以自动推断出返回值类型）时，这部分可以省略。
//五、{ 函数体 }，标识函数的实现，这部分不能省略，但函数体可以为空。