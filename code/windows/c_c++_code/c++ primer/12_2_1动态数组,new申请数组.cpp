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

std::string *mystrstr(const std::string str1, const std::string str2)
{
	std::string *str = new std::string(str1 + str2);
	return str;
}

char * transformCinToStr()
{
	int num = 0;
	std::string word;
	std::string sentence;
	while (std::cin >> word)
		sentence += word;
	char * ret = new char[sentence.size() + 1];
	strcpy_s(ret, sentence.size() + 1, sentence.c_str());
	return ret;
}

int main12_2_1()
{
	//通过new申请数组,返回的是指向数组头的指针
	int* arr = new int[42];
	//new数组支持参数列表初始化
	int* arr2 = new int[3]{1,2,3};
	std::cout << arr2[0] << arr2[1] << arr2[2] << std::endl;
	//删除动态数组的操作,删除时底层为逆序删除
	delete[]arr;
	delete[]arr2;
	//标准库提供了一种用unique_ptr管理动态数组的方法,即用动态数组来初始化unique_ptr,并支持下标访问
	std::unique_ptr<int[]> uptr(new int[3]{4,5,6});
	std::cout << uptr[0] << uptr[1] << uptr[2] << std::endl;
	//release和reset成员函数会调用delete[]来删除其所指向的动态数组
	uptr.release();
	//若用shared_ptr来管理动态数组,需要传入自己设定的delete,并且由动态数组初始化的shared_ptr未重载下标运算符,且智能指针本身不支持下标运算
	//所以用shared_ptr来管理动态数组,其访问方式与unique_ptr来管理有所偏差
	std::shared_ptr<int> sptr(new int[3]{7,8,9}, [](int *p) {delete[]p; });
	for (int i = 0; i < 3; i++)
		std::cout << *(sptr.get() + i) << std::ends;
	std::cout << std::endl;

//练习题:
	std::string* str = mystrstr("hello,", "world");
	std::cout << *str << std::endl;
	delete str;

	char * str2 = transformCinToStr();
	std::cout << str2 << std::endl;
	delete[]str2;

	system("pause");
	return 0;
}
