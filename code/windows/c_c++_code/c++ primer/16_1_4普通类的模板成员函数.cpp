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

class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr):os(s){}
	template<typename T>
	void operator()(T* p) const
	{
		os << "deleting unique_ptr" << std::endl; delete p;
	}
private:
	std::ostream &os;
};

int main16_1_4()
{
	DebugDelete d;
	double* p = new double;
	//d(p);//合理,隐式指定模板类型
	d.operator() < double > (p);//合理,显式指定模板类型
	//d<double>(p);//不合理,不知道该如何在此形式下显式指定
	int *ip = new int;
	DebugDelete()(ip);

	system("pause");
	return 0;
}