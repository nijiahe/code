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


int main14_8_2()
{
	std::vector<int> v1{ 3,4,3,5,3,6,3,7 };
	std::sort(v1.begin(), v1.end(), std::greater<int>());
	for (auto num : v1)
		std::cout << num << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}
