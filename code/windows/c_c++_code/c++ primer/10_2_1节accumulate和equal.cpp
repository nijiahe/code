#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_1()
{
	std::vector<int> v1{ 1,2,3,4,5,6 };
	int num = std::accumulate(v1.begin(), v1.end(), 0);//将vector中的所有数字加到第三个元素上
	std::cout << num << std::endl;

	std::vector<std::string> v2{ "he","llo"," ","wor","ld" };
	std::string str = std::accumulate(v2.begin(), v2.end(), std::string(""));//将accumulate也可用连接string字符，但第三个元素要是string，因为char类型没有重载'+'
	std::cout << str << std::endl;

	std::vector<int> v3{ 1,2,3,4,5,6,7 };
	//第一二个参数代表一个容器的范围，第三个表示要比较的那个容器
	//当第一二个参数范围内指定的元素第三个参数按顺序一一对应,就返回1,假定第三个参数与前面一样长，实际上可以比第一二个参数确定的范围更大
	std::cout << std::equal(v1.begin(), v1.end(), v3.begin()) << std::endl;

	system("pause");

	return 0;
}