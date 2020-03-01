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

//��ϰ��
/*
ע��:
1.typename��classû������
2.ÿ��ģ������ǰ���붼����typename����class,������typename T,U����
*/
template<typename T,class U>
int compare(const T& v1, const T& v2)
{
	if (v1 < v2)return -1;
	else if (v2 < v1) return 1;
	else return 0;
}

template<unsigned N,unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M]) {
	return std::strcmp(p1, p2);
}

template<typename Iterator, typename Value>
Iterator find2(Iterator begin, Iterator end, const Value &val)
{
	for (; begin != end; begin++)
		if (*begin == val)
			return begin;
}

template<typename T, unsigned N>
T* begin(const T(&arr)[N])
{
	return arr;
}

template<typename T, unsigned N>
T* end(const T(&arr)[N])
{
	return arr + N;
}

int main16_1_1()
{
	std::cout << compare<bool,int>(true, false) << std::endl;
	std::vector<int> vec1{ 1,2,3 }, vec2{ 4,5,6 };
	std::cout << compare<std::vector<int>, int>(vec1, vec2) << std::endl;

	char p1[] = "123", p2[] = "45";
	std::cout << compare(p1, p2) << std::endl;
	std::vector<int> vec3{ 1,2,3,4,5,6,99,5,8,2 };
	std::cout << *find2(vec3.begin(), vec3.end(), 99) << std::endl;

	system("pause");
	return 0;
}