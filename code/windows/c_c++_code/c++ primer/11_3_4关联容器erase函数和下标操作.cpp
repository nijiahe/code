#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>


int main11_3_4()
{
	std::map<std::string, int> map{ {"a",2},{"bb",5},{"cc",9} };
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair) 
	{std::cout << "Key:" << pair.first << ",Value:" << pair.second << std::endl; });
	//erase函数返回删除掉的关键字的数量,对于不重复关联容器,该值总是0或1
	int count = map.erase("cc");
	std::cout << "The cc has been removed,the count is " << count << std::endl;
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair)
	{std::cout << "Key:" << pair.first << ",Value:" << pair.second << std::endl; });

	/*对map的下标操作有以下过程:
	1.寻炸此下标对应的关键字key
	2.若找到,返回此关键字对应的value
	3.若未找到,则会新插入这样的一个关键字key作为新元素
	*/

	system("pause");
	return 0;
}