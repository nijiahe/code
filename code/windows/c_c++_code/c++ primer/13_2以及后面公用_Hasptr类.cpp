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

class Hasptr
{
public:
	friend void swap(Hasptr&, Hasptr&);
	Hasptr(const std::string &s = std::string()) :ps(new std::string(s)), i(0) {}
	Hasptr(const Hasptr &hp) :ps(new std::string(*(hp.ps))), i(hp.i) {}
	~Hasptr() { delete ps; };
	Hasptr& operator=(const Hasptr &hp)//注:拷贝运算符只会复制非static成员
	{
		std::string *new_ps = new std::string(*hp.ps);
		delete ps;
		ps = new_ps;
		i = hp.i;
		return *this;
	}
private:
	std::string *ps;
	int i;
};

//重载Hasptr的swap
inline
void swap(Hasptr &lhs, Hasptr &rhs)
{
	using std::swap;//不知道为什么,459页上说原因会在616页和706页说明
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "function in swap(Hasptr &lhs, Hasptr &rhs)" << std::endl;
}

int main13_2()
{


	system("pause");
	return 0;
}
