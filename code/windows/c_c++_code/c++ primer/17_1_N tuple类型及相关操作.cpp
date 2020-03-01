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
	std::tuple����������std::pair����,��֮ͬ����pair�����ǹ̶���������Ա,��tuple���ͳ�Ա�������̶�
	*/
	std::tuple<std::size_t, std::size_t, std::size_t> threeD1;//Ĭ�ϳ�ʼ��
	std::tuple < std::string, std::vector<double>, int, std::list<int>> someVal("constants", { 3.14,2.718 }, 42, { 0,1,2,3,4,5 });//���캯����ʼ��
	std::tuple<std::size_t, std::size_t, std::size_t> threeD{ 1,2,3 };//����std::initializer_list��ʽ�Ĺ��캯��
	std::tuple<std::size_t, std::size_t, std::size_t> threeD2 = { 1,2,3 };//��������?
	auto item = std::make_tuple("0-999-78345-x", 3, 20.00);//make_tuple����

	//���tuple�еı���,ע��getӦ����һ����tuple���Աģ�庯��,ģ������Ϊtemplate<unsigned N>
	//��Ȼstd::get<N>(tuple)���ص�������std::tuple_element<N,decltype(item)>,������Ӧ�ö�����ת��Ϊstd::string��ǿת����,����Ҳ������std::string������
	typedef decltype(item) trans;
	//����std::get<N>(tuple>������tuple������ΪN�ı���
	std::tuple_element<0, decltype(item)>::type book = std::get<0>(item);
	std::string book2 = std::get<0>(item);
	size_t sz = std::tuple_size<decltype(item)>::value;
	std::cout << "Book: " << book << "tuple size: " << sz << std::endl;

	system("pause");
	return 0;
}