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

/*16_3*/
template<typename T>
std::string debug_req(const T &t)
{
	std::ostringstream ret;
	ret << t;
	return ret.str();
}

/*16_4*//*ʹ��sizeof(Args/args)��ӡ�ɱ������*/
template<typename T,typename...Args>
void foo(const T &t, const Args...args)
{
	std::cout << sizeof...(Args) << std::ends;//sizeof...��������ͳ�Ʋ�ͬ���͵�����
	std::cout << sizeof...(args) << std::endl;//sizeof...��������ͳ�ƿɱ����������
}

/*16_4_1*//*�������ö�һ���Ĳ���,��ʵ�ֿɱ�����ݹ����*/
//��������൱�ڵݹ���ֹ����,������������ƥ��ԭ��,�ں������Ͽɱ����ֻʣ��������ʱ,��ƥ�䵽�������,�����������Ǹ��ɱ�κ���
template<typename T>
std::ostream &print(std::ostream &os, const T &t)
{
	return os << t << std::endl;
}

template<typename T, typename...Args>
std::ostream &print(std::ostream &os, const T&t, const Args...rest)
{
	os << t << ",";
	return print(os, rest...);//����ÿ�ξ���һ��ԭ������rest�еĲ���������Ϊ��const T& t
}

/*16_4_2*//*����չ*/
template<typename...Args>
std::ostream &errorMsg(std::ostream &os, const Args...rest)
{
	return print(os, debug_req(rest)...);
	//�൱�ڱ�д��return print(os, debug_req(rest1),debug_req(rest2),debug_req(rest3)�ȵ�),��debug_req(...)��������չ
}


int main16_4_N()
{
	/*16_4*/
	int i = 0; double d = 3.14; std::string s = "how now brown cow";
	foo(i, s, 42, d);
	foo(s, 42, "hi");
	foo(d,s);
	foo("hi");

	/*16_4_1*/
	print(std::cout, i, s, 42);

	/*16_4_2*/
	errorMsg(std::cout, i, s, 42);

	system("pause");
	return 0;
}