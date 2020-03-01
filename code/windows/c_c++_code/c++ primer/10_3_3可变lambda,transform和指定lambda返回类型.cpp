#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

int mainmain10_3_3()
{
	std::vector<int> v{ 1,-1,2,-3,-5,4,-6,-1 };
	//transform算法:接受三个迭代器和一个函数,前两个迭代器确定范围,第三个迭代器确定目的位置
	//对每个范围内元素调用第四个参数所确定的可调用对象,并将返回值写入目的位置
	std::transform(v.begin(), v.end(), v.begin(),[](int i) {return i > 0 ? i : -i; });
	for_each(v.begin(), v.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;

	/*
	*注:我的环境下这样好像是可以的
	//注:若lambda表达式中除了return语句以外还有别的语句,若未指定返回值,则返回值只能为void,如下行代码是错误的
	std::transform(v.begin(), v.end(), v.begin(), [](int i) 
	{if (i > 0)return i; else return -i; });
	for_each(v.begin(), v.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	*/

//练习题:
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	int count = std::count_if(v1.begin(), v1.end(), [](std::string s)->bool { return s.size() >= 4; });
	std::cout << "There is " << count << " numbers of words compatible with the condition" << std::endl;

	int n = 5;
	auto func = [&n]()->bool {while (n > 0)--n; return n == 0 ? 1 : 0; };
	bool flag = func();
	std::cout << "Now the number n is " << n << ",and the flag is " << flag << std::endl;

	system("pause");
	return 0;
}