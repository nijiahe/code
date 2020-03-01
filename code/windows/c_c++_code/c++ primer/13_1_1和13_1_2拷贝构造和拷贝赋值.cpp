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

class Hasptr2
{
public:
	Hasptr2(const std::string &s = std::string()):ps(new std::string(s)),i(0){}
	Hasptr2(const Hasptr2 &hp):ps(new std::string(*(hp.ps) ) ),i(hp.i){}
	~Hasptr2() { delete ps; };
	Hasptr2& operator=(const Hasptr2 &hp)//注:拷贝运算符只会复制非static成员
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

int main13_1_1()
{
	

	system("pause");
	return 0;
}
