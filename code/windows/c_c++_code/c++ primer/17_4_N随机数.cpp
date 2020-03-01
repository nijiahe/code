#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <cstring>
#include <type_traits>
#include <tuple>
#include <bitset>

#include <random>
#include <ctime>

int main17_4_N()
{
	std::default_random_engine e;
	e.seed(time(0));
	std::uniform_int_distribution<unsigned> u(0, 9);//int表示整形类型数
	for (size_t i = 0; i < 10; ++i)
		std::cout << u(e) << std::ends;
	std::cout << std::endl;

	std::uniform_real_distribution<double> u2(0, 1);//real表示实数范围
	for (size_t i = 0; i < 10; ++i)
		std::cout << u2(e) << std::ends;
	std::cout << std::endl;

	std::normal_distribution<double> n(4, 1.5);//正态分布,EX=4,DX=(1.5)^2
	std::vector<unsigned> vals(9);
	for (std::size_t i = 0; i != 200; ++i) {
		unsigned v = lround(n(e));
		if (v < vals.size())
			++vals[v];
	}
	for (std::size_t j = 0; j != vals.size(); ++j)
		std::cout << j << ": " << std::string(vals[j], '*') << std::endl;

	std::bernoulli_distribution b(0.55);//伯努利分布,p=0.55


	system("pause");
	return 0;
}