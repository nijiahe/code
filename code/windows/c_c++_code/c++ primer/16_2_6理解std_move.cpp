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

/*
std::move�ڱ�׼���µ�ʵ��
��ͨ��remove_reference::typeȡ������������������(����:����42ȡint,��ֵint&Ҳȡint)
Ȼ������ֵȴ��int&&,����static_cast��intת��Ϊ��int&&,�����std::move���ڲ�������
*/
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t)
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}


int main16_2_6()
{
	

	system("pause");
	return 0;
}