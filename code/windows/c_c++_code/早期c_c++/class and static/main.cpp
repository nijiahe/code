#include<iostream>

using namespace std;

/*①*//*普通类中的static成员*/
/*结论：
1.普通类中的static成员变量可以直接访问(如果是public)
2.普通类中的static成员变量也可以通过类的实例访问
3.普通类中的static成员函数可以直接访问，也可以通过类的实例访问
4.普通类中的static成员函数只能访问static成员，因为只有这种成员是全局都存在的,访问别的成员会出现调用了这个函数而无法访问*/
/*补充:
1.普通类中的普通类型成员变量不能直接通过类名访问,必须通过类的实例访问,因为在这之前类还未被构造出来
2.普通类中的普通类型成员函数不能直接通过类名访问,必须通过类的实例访问,因为在这之前类还未被构造出来*/
class test
{
public:
	int x = 0;
	int y;
	static int testx;
	static void show();/*定义在类内和类外都可以*/
	/*{
		cout << testx << endl;
	}*/
	void run()
	{
		cout << "run" << endl;
	}
};
int test::testx = 0;
void test::show()
{
	{
		cout << testx << endl;
	}
}
void main01()
{
	test::show();
	test test1;
	test1.show();
	cout << test::testx << endl;
	cout << test1.testx << endl;
	/*cout << test::x << endl;
	cout << test::y << endl;*/
	cout << test1.x << endl;
	cout << test1.y << endl;
	/*test::run();*/
	test1.run();
	std::cin.get();
}
/*************************************************************************************************************************
**************************************************************************************************************************/
/*②*//*模板类中的static*/
/*结论:
1.模板类中的staitc成员变量可以在类给定具体类型后访问,也可以创建了类的实例后通过类的实例访问对应类型
2.模板类中的static成员变量每种类的具体类型共享一个
3.模板类中的static成员函数可以给定类型后直接访问，也可以通过类的实例访问
4.模板类中的static成员函数只能访问static成员，因为只有这种成员是全局都存在的,访问别的成员会出现调用了这个函数而无法访问*/
template<class T>
class test2
{
public:
	T x = 0;
	static T textx2;
	test2()
	{
		this->textx2++;
	}
	static void show2();
};
template<class T>
T test2<T>::textx2 = 0;

template<class T>
void test2<T>::show2()
{
	cout << test2<T>::textx2 << endl;
}

void main02()
{
	test2<int> tes2;
	cout << tes2.textx2 << endl;
	test2<int>::show2();
	test2<double>::show2();
	std::cin.get();
}

/*************************************************************************************************************************
**************************************************************************************************************************/
/*③*//*继承类父类中的static成员*/
/*结论:
1.继承类父类中的static成员变量仍然可以不通过类的实例化直接访问,也可以通过类的实例访问
2.继承类父类中的static成员函数仍然可以不通过类的实例化直接访问,也可以通过类的实例访问*/
/*补充:
1.不能通过类名直接访问类中的普通函数、成员,因为他们都没有实例化
2.被继承的类中的父类的static成员仍与原来那个共享
3.没被实例化就可以访问的只有static成员
4.继承类中的子类虽然包含父类,但是是不存在父类中的实例的,所以要访问父类中的变量或者方法只能通过实例后的子类再加上::访问*/
class test3 :public test
{
	int testx3;
};
void main03()
{
	test3 tes3;
	cout << tes3.test::x << endl;//输出0
	cout << tes3.test::y << endl;//输出随机数
	cout << test3::test::testx << endl;
	test::testx = 1;
	cout << test3::test::testx << endl;
	test3::test::show();
	/*test3.test.show();*/
	std::cin.get();
}
/*④*//*继承类父类是类模板情况下的static成员*/
/*结论:
1.继承类父类中的static成员可以在子类给定类型后访问对应类型的父类,也可以通过子类实例访问
2.或者可以给定子类类型后再给定子类中继承的父类的类型从而做到访问不同类型的父类成员
3.但实例化以后继承类中的父类就有了固定类型,因为子类实例化后,继承相当于只继承相对应类型的父类,就不能达到访问其他类型的父类*/
template<class T>
class test4 :public test2<T>
{
	int x;
};
void main()
{
	test2<double> db1;
	cout << test4<double>::test2::textx2 << endl;
	cout << test4<int>::test2<double>::textx2 << endl;
	cout << test4<int>::test2<int>::textx2 << endl;
	cout << db1.test2::textx2 << endl;
	std::cin.get();
}