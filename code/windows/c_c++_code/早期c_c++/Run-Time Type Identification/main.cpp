#include<iostream>

using namespace std;

class test1
{
public:
	int test1x=1;
	virtual void show()
	{
		cout << "test1 show" << endl;
	}
	void run()
	{
		cout << test1x << endl;
	}
};
class test2:public test1
{
public:
	int test2x=2;
	void show()
	{
		cout << "test2 show" << endl;
	}
	void run()
	{
		cout << test2x << endl;
	}
};

void main()
{
	test1* tes1 = new test1;
	test1* tes2 = new test2;
	cout << typeid(tes1).name() << "  " << typeid(tes2).name() << endl;
	cout << typeid(*tes1).name() << "  " << typeid(*tes2).name() << endl;
	/*如果在父类中定义一个虚函数,子类继承了父类,则子类也含有一个虚函数指针,typeid就会依据虚函数指针中的内容来选择正确的类构造函数来获取类型*/
	cout << (typeid(tes1) == typeid(tes2)) << endl;
	/*typeid重载了!=和==*/
	test2* tes3 = nullptr;
	tes1->run();
	/*static_cast就是单纯的改变指针指的大小,原来有的数据照样能反应，扩展出来的数据输出随机值,不安全*/
	/*tes3 = static_cast<test2*>(tes1);/*此种方法强转编译器根据偏移字节数输出一个随机值
	static_cast会重新申请合适大小的内存*/
	tes3 = dynamic_cast<test2*>(tes1);/*dynamic_cast则可以根据创建的类型来转换至合适的类型,但是因为转换为了子类,体积变大,但实际体积不变
									  所以如果调用函数来输出子类特有的成员就会报错，比较安全
									  在static_cast的基础上添加了无法访问原来未申请部分的内存的功能,比较安全*/
	/*cout << sizeof(*tes3) << endl;/*sizeof只是根据指针指着的大小来获得内存,这里获得的内存并不一定向操作系统申请过*/
	tes3->run();
	/*dynamic_cast<T>()是c++用于转换子类和父类的函数,但要成功转换需要父类有虚函数*/
	cout << (*tes3).test2x << endl;

	std::cin.get();
}