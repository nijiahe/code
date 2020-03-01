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

void f(int v1, int& v2)
{
	std::cout << v1 << " " << ++v2 << std::endl;
}
void g(int &&i, int &j)
{
	std::cout << i << " " << j << std::endl;
}

/*
��ʹ��ģ�庯����ģ�����ͽ��ղ���ʱ,��������ģ�庯��
����ϣ��ͨ��flip1����f���ı�v2��Ϊһ�������������ֵ
��ֱ�ӵ���f(42,i),���ܹ�����Ԥ�ڽ��е�,��������������flip1(f,42,i),flip1��ʵ����Ϊflip(func*,int,int),��Ȼ������Ԥ��һ����
��������flip2�İ汾,�˰汾���������۵�,��������ֵ����Ϣ,�������ǵ���flip2(g,42,i),����42�ᱻ����Ϊint,��flip2��ʵ����Ϊflip2(func*,int,int)//ע��:���ǲ�̫��,Ҳ��̫ȷ��
������std::forward<T>(t)���Ա�����������Ϣ
*/
template<typename F,typename T1,typename T2>
void flip1(F f, T1 t1, T2 t2)
{
	f(t1, t2);
}
template<typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
	f(t1, t2);
}
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
	std::cout << typeid(t1).name() << typeid(t2).name() << std::endl;
	f(std::forward<T1>(t1), std::forward<T2>(t2));
}


int main16_2_7()
{
	int i = 1;
	flip(g, 42, i);

	system("pause");
	return 0;
}