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

template<typename> class T2;

//����Ϊģ���ṩĬ��ʵ��,�ڶ���ģ�������ʱ�ں������<>��ʾ����һ��ģ��
template<typename T=int>
class T1
{
public:
	//friend class T3;//T3����ģ����,��ʱΪ��ģ�������Ԫ������ʽ
	//template <typename X>friend class T2;//���е�T2��ΪT1����Ԫ��,��ʱ����ģ����ѡ�õ�ģ�������Ӧ����౾���ģ����ͬ
	//����Ϊһ��һ��Ԫ��ϵ,ֻ�ö�Ӧʵ����T2��ΪT1����Ԫ,����ʱ������T1֮ǰ����T2��һ����Ԫ��,
	//�����������Ӧ��֪��T2��һ��ģ�������<>������Ϊ�﷨����
	friend class T2<T>;
	friend T;//��c++11��,���Խ�����ģ����������Ϊ��Ԫ,��T����һ����Foo,��ô��ʱFoo��T1<Foo>����Ԫ��
	T data = 99;
};

template<typename T>
class T2
{
	T1<int> t1;
	T data;
};

class T3
{
	int t3;
};


int main16_1_2()
{
	T1<> t1;
	std::cout << t1.data << std::endl;
	system("pause");
	return 0;
}