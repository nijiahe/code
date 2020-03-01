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

int add(int a, int b) { return a + b; }
class devide
{
public:
	int operator()(int a, int b) { return a / b; };
};
auto mod = [](int a, int b) {return a % b; };

auto binops = std::map<std::string, std::function<int(int, int)>>
{
	{"+",add},
	{"-",std::minus<int>()},
	{"/",devide()},
	{"*",[](int a,int b) {return a * b; }},
	{"%",mod}
};

int main14_8_3()
{
	/*
	 lambda���ʽ��ʵ����һ����
	 ����ָ��������ʵ���Ǻ���ָ��
	 ��ͨ����ָ��������Ǻ���ָ��
	 Ϊ������ͳһΪͬһ������,��׼�ⶨ����function��
	 function������ɺ���ָ��,���������lambda���ʽ��ʼ��
	 ע��:�������ع��ĺ���,����һ�����ֶ�Ӧ�˺ö��������ͬ�ĺ���,����ͨ����ָ��ȡ���ֻ�Ϊ�䴴�������ʽ�ķ�ʽ��ȡ��.�Ӷ�����������
	 */
	std::string ops;
	int a, b;
	while (std::cin >> ops >> a >> b)
	{
		std::cout << binops[ops](a, b) << std::endl;
	}

	system("pause");
	return 0;
}