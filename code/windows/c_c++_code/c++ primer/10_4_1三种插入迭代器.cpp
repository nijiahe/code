#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>


int mainmain10_4_1()
{
	/*
	ע��:һЩ����ĵ�����������ͷ�ļ�<iterator>��
	���ֲ��������:
	1.std::back_inserter	����һ��ʹ��push_back�ĵ�����
	2.std::front_inserter	����һ��ʹ��push_front�ĵ�����
	3.std::inserter			����һ��ʹ��insert�ĵ�����,�˺������ܵڶ�������,����ָ��һ�����������ĵ�����,Ԫ�ؽ������뵽�˸�����������ָԪ��֮ǰ
	�Բ������������,*it,++it,it++,--it,it--��itû���κ�����,ÿ�ֲ���������it
	*/

//��ϰ��:
	std::vector<int> v1{ 1,3,5,7,6,1,3,9,8,1,3,4,8 };
	std::sort(v1.begin(), v1.end());
	std::vector<int> v2;
	std::back_insert_iterator<std::vector<int> > biter = std::back_inserter(v2);
	std::unique_copy(v1.begin(), v1.end(), biter);
	std::for_each(v2.begin(), v2.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;

	std::vector<int> v3{ 1,2,3,4,5,6,7,8,9 };
	std::list<int> list1;
	std::insert_iterator<std::list<int> > ins = std::inserter(list1, list1.begin());//insert_iterator����������inserth
	std::copy(v3.begin(), v3.end(), ins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	list1.clear();
	std::back_insert_iterator<std::list<int> > bins = std::back_inserter(list1);//back_insert_iterator����������push_back
	std::copy(v3.begin(), v3.end(), bins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	list1.clear();
	std::front_insert_iterator<std::list<int> > fins = std::front_inserter(list1);//front_insert_iterator����������push_front
	std::copy(v3.begin(), v3.end(), fins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;


	system("pause");
	return 0;
}