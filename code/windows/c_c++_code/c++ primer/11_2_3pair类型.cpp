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

int main11_2_3()
{
//��ϰ��:
	std::string words;
	int num;
	std::vector<std::pair<std::string, int> > vec;
	while (std::cin >> words >> num)
	{
		//vec.push_back(std::make_pair(words, num));
		//�������ִ���std::pair�ķ���:
		vec.push_back({words,num});
		//vec.push_back(std::pair<std::string,int>(words,num));
	}
	std::for_each(vec.begin(), vec.end(), [](std::pair<std::string, int> pairs)
	{std::cout << "The key is " << pairs.first << " ,and the value is " << pairs.second << std::endl; });


	system("pause");
	return 0;
}