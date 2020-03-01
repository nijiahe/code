#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <vector>

bool isBiggerOrEqual(const std::string &s, std::string::size_type sz)
{
	return s.size() >= sz;
}

int mainmain10_3_4()
{
	/*
	�������龰:���еĿɵ��ò����Ĳ����б����㷨��Ҫ�Ĳ�ƥ��,����������������������:
	1.���㷨����Ĳ�������lambda���ʽ,lambda���ʽ����ֵ,Ȼ�����亯�����ڵ�����д�õĿɵ��ò���
	2.ͨ��bind�����󶨸�����ֵ���㷨,bind����ͨ��ռλ������һ��ֻ��ռλ����ռ�Ĳ���λ�õ��������������º���,���������βδ���������ֵ
	����std::cout << typeid(isB).name() << std::endl����,std::bind���ص�������һ���ܸ��ӵĶ���
	std::bind���Ը�������,�������ڵ���������˳��,��:
	auto g = bind(f,a,b,_2,c,_1);//f��һ����5�������ĺ���
	��g(_1,_2)��Ӧӳ��Ϊf��(a,b,_2,c,_1);
	��bind�����´�������,������������ostream,���ܱ�����,��ʱͨ����׼���ref()��������������,ref()������funcitonalͷ�ļ���
	*/

//��ϰ��
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	int sz = 4;
	auto isB = std::bind(isBiggerOrEqual, std::placeholders::_1, sz);
	int count = std::count_if(v1.begin(), v1.end(), isB);
	std::cout << "There is " << count << " numbers of words compatible with the condition" << std::endl;

	std::string  str("123456");
	bind(isBiggerOrEqual, std::placeholders::_1, str.size());
	std::vector<std::string>::iterator it = std::find_if(v1.begin(), v1.end(), bind(isBiggerOrEqual, std::placeholders::_1, str.size()));
	std::cout << "The first words compatible with the condition is '" << *it << "'" <<std::endl;


	system("pause");
	return 0;
}