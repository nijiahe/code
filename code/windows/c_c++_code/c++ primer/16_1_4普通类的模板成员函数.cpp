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
	//d(p);//����,��ʽָ��ģ������
	d.operator() < double > (p);//����,��ʽָ��ģ������
	//d<double>(p);//������,��֪��������ڴ���ʽ����ʽָ��
	int *ip = new int;
	DebugDelete()(ip);

	system("pause");
	return 0;
}