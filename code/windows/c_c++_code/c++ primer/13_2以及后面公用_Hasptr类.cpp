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
	Hasptr& operator=(const Hasptr &hp)//ע:���������ֻ�Ḵ�Ʒ�static��Ա
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

//����Hasptr��swap
inline
void swap(Hasptr &lhs, Hasptr &rhs)
{
	using std::swap;//��֪��Ϊʲô,459ҳ��˵ԭ�����616ҳ��706ҳ˵��
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "function in swap(Hasptr &lhs, Hasptr &rhs)" << std::endl;
}

int main13_2()
{


	system("pause");
	return 0;
}
