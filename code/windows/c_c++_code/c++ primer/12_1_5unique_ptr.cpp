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

int main12_1_5()
{
//¡∑œ∞Ã‚:
	std::unique_ptr<std::string> ptr1(new std::string("123"));
	std::unique_ptr<std::string> ptr2(new std::string("456"));
	//std::unique_ptr<std::string> ptr3(ptr1);
	//ptr2 = ptr1;

	system("pause");
	return 0;
}
