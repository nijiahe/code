#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_3()
{
	std::vector<int> v1{ 1,3,5,7,6,1,3,9,8,1,3,4,8 };
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	//sort�㷨,STL�еĿ��������㷨,��<�Ĳ��ԶԴ���ĵ�����ȷ���ķ�Χ���п�������
	std::sort(v1.begin(), v1.end());
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	//unique�㷨,����Ϊ�������ڵ��ظ�Ԫ,����һ��������ָ����Щ�ظ�Ԫ�صĿ�ʼλ��
	//std::unique�����ı������Ĵ�С
	//ע��:��ʱ����β������ЩԪ��ԭ����ɶ���ڻ���ɶ����û�б�
	std::vector<int>::iterator end_unique = std::unique(v1.begin(), v1.end());
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	v1.erase(end_unique, v1.end());//����vector������vector�㷨����������������ɾ�����м������
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}