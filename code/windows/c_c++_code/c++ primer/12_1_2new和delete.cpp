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

std::vector<int>* creatIntVec()
{
	return new std::vector<int>;
}

void readInVec(std::vector<int>* &vec)
{
	int num;
	while (std::cin >> num)
		vec->push_back(num);
}

void printAndDeleteVec(std::vector<int>* &vec)
{
	std::for_each(vec->begin(), vec->end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	delete vec;
	vec = nullptr;
}

int main12_1_2()
{
	//������,new�ᰴ���乹�캯�����й���,��������������,Ĭ�ϳ�ʼ���Ľ����δ�����,Ҫ�������ֵ��ʼ��,ֻ����new����������()����
	int* num1 = new int;//num1��һ�������
	int* num2 = new int();//num2��0
	std::cout << "num1 is " << *num1 << ",and meantime num 2 is " << *num2 << std::endl;

	//����new auto()ʹ�������Զ��Ʋ�Ҫnew������
	std::string str;
	auto str2 = new auto(str);
	std::cout << typeid(str2).name() << std::endl;

	//���ڴ�ľ�,new���׳�std::bad_alloc,Ҫ��ֹ�׳���ʹ��(nothrow),��ʱnew�᷵��һ����ָ��
	int* num3 = new(std::nothrow) int();

//��ϰ��:
	auto vec = creatIntVec();
	readInVec(vec);
	printAndDeleteVec(vec);
	std::cout << "Now the vec is " << vec << std::endl;

	system("pause");
	return 0;
}
