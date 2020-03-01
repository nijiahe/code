#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

void elimDups2(std::vector<std::string> &v)
{
	std::sort(v.begin(), v.end());
	std::vector<std::string>::iterator end_unique = std::unique(v.begin(), v.end());
	v.erase(end_unique, v.end());
}

void biggies1(std::vector<std::string> &v, std::string::size_type sz)
{
	elimDups2(v);
	std::stable_sort(v.begin(), v.end(), [](std::string s1, std::string s2)->bool
	{return s1.size() < s2.size(); });
	std::vector<std::string>::iterator iter = std::find_if(v.begin(), v.end(), [sz](std::string s)->bool
	{return s.size() >= sz; });
	int count = v.end() - iter;
	std::cout << "There is " << count << " words compatible with the condition" << std::endl;
	std::for_each(iter, v.end(), [](const std::string &s) {std::cout << s << std::ends; });
	std::cout << std::endl;
}

void biggies2(std::vector<std::string> &v, std::string::size_type sz)
{
	elimDups2(v);
	std::stable_sort(v.begin(), v.end(), [](std::string s1, std::string s2)->bool
	{return s1.size() < s2.size(); });
	std::vector<std::string>::iterator iter = std::stable_partition(v.begin(), v.end(), [sz](std::string s)->bool
	{return s.size() >= sz; });
	int count = iter - v.begin();
	std::cout << "There is " << count << " words compatible with the condition" << std::endl;
	std::for_each(v.begin(), iter, [](const std::string &s) {std::cout << s << std::ends; });
	std::cout << std::endl;
}

int mainmain10_3_2()
{
//练习题
	int (*f1)(int,int) = [](int i, int j)->int {return i + j; };
	std::cout << f1(1, 2) << f1(3, 4) << std::endl;

	int num = 111;
	auto f2 = [num](int i)->int {return num + i; };
	std::cout << f2(3) << f2(6) << std::endl;
	//std::cout << typeid(f2).name() << std::endl;//一个奇怪的类型,有捕获的lambda表达式好像不能通过平常的函数指针方式创建

	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	biggies2(v1, 4);

	system("pause");
	return 0;
}