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

/*���Զ�һ��ģ�����������,��ָ����ָ��ģ������ʱ���ر����*/
template<typename T>
int compare(const T& v1, const T& v2)
{
	if (v1 < v2)return -1;
	else if (v2 < v1) return 1;
	else return 0;
}

//������const char*����
template<> //template<>��������һ��������ģ�庯��,������һ����ͨ��ģ�庯��
int compare(const char *const &p1, const char *const &p2)
{
	return strcmp(p1, p2);
}

/*
����������:
��������������˼���Ƕ�һ��ģ�����ͱ���template<typename T,typename U>�����ӵ�ָ����T��ʲô
���Ǹ����䴫��Ĳ����ľ�������������������,����,����Ĳ�����һ����ֵint &,������һ����ֵint &&,ͨ����������Ĳ�ͬ�����ʼ�������
��׼���std::remove_reference���;������˲���������,�Դ����������ֵ����ֵ������½����˲�ͬ������,������ʾ:
*/
//����ͨ�����,ɶҲ����,��remove_reference::type��������Ȼ��ԭ������ͬ
template<class T> struct remove_reference {
	typedef T type;
};
//Ϊ�����������ֵ����ʱ����������
template<class T> struct remove_reference<T &> { 
	typedef T type;
};
//��ֵ
template<class T> struct remove_reference<T &&> { 
	typedef T type;
};

//������������ȥ���������͵��������Ի�����ֵ����.type��Ϊ������ͨ������,������ֵ,�ȿɶ�Ҳ��д

int main16_5()
{
	
	system("pause");
	return 0;
}