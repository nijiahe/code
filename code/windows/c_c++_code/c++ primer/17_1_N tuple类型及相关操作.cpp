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
#include <tuple>


int main17_1_1()
{
	/*
	std::tuple类型类似于std::pair类型,不同之处是pair类型是固定的两个成员,而tuple类型成员数量不固定
	*/
	std::tuple<std::size_t, std::size_t, std::size_t> threeD1;//默认初始化
	std::tuple < std::string, std::vector<double>, int, std::list<int>> someVal("constants", { 3.14,2.718 }, 42, { 0,1,2,3,4,5 });//构造函数初始化
	std::tuple<std::size_t, std::size_t, std::size_t> threeD{ 1,2,3 };//接受std::initializer_list方式的构造函数
	std::tuple<std::size_t, std::size_t, std::size_t> threeD2 = { 1,2,3 };//拷贝构造?
	auto item = std::make_tuple("0-999-78345-x", 3, 20.00);//make_tuple构造

	//获得tuple中的变量,注意get应该是一个非tuple类成员模板函数,模板类型为template<unsigned N>
	//虽然std::get<N>(tuple)返回的类型是std::tuple_element<N,decltype(item)>,但是他应该定义了转化为std::string的强转方法,所以也可以用std::string来接收
	typedef decltype(item) trans;
	//利用std::get<N>(tuple>来返回tuple的序列为N的变量
	std::tuple_element<0, decltype(item)>::type book = std::get<0>(item);
	std::string book2 = std::get<0>(item);
	size_t sz = std::tuple_size<decltype(item)>::value;
	std::cout << "Book: " << book << "tuple size: " << sz << std::endl;

	system("pause");
	return 0;
}