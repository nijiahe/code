#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <vector>

bool isBiggerOrEqual(const std::string &s, std::string::size_type sz)
{
	return s.size() >= sz;
}

int mainmain10_3_4()
{
	/*
	有如下情景:已有的可调用参数的参数列表与算法需要的不匹配,有以下两个方法进行适配:
	1.向算法所需的参数传递lambda表达式,lambda表达式条件值,然后在其函数体内调用以写好的可调用参数
	2.通过bind函数绑定该条件值和算法,bind函数通过占位符返回一个只将占位符所占的参数位置当作函数参数的新函数,在其他的形参处填上条件值
	根据std::cout << typeid(isB).name() << std::endl来看,std::bind返回的类型是一个很复杂的东西
	std::bind可以隔参数绑定,可以用于调整参数的顺序,如:
	auto g = bind(f,a,b,_2,c,_1);//f是一个由5各参数的函数
	则g(_1,_2)对应映射为f是(a,b,_2,c,_1);
	但bind函数会拷贝其参数,如果参数里存在ostream,则不能被拷贝,这时通过标准库的ref()函数传入其引用,ref()定义在funcitonal头文件中
	*/

//练习题
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	int sz = 4;
	auto isB = std::bind(isBiggerOrEqual, std::placeholders::_1, sz);
	int count = std::count_if(v1.begin(), v1.end(), isB);
	std::cout << "There is " << count << " numbers of words compatible with the condition" << std::endl;

	std::string  str("123456");
	bind(isBiggerOrEqual, std::placeholders::_1, str.size());
	std::vector<std::string>::iterator it = std::find_if(v1.begin(), v1.end(), bind(isBiggerOrEqual, std::placeholders::_1, str.size()));
	std::cout << "The first words compatible with the condition is '" << *it << "'" <<std::endl;


	system("pause");
	return 0;
}