#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_1()
{
	std::vector<int> v1{ 1,2,3,4,5,6 };
	int num = std::accumulate(v1.begin(), v1.end(), 0);//��vector�е��������ּӵ�������Ԫ����
	std::cout << num << std::endl;

	std::vector<std::string> v2{ "he","llo"," ","wor","ld" };
	std::string str = std::accumulate(v2.begin(), v2.end(), std::string(""));//��accumulateҲ��������string�ַ�����������Ԫ��Ҫ��string����Ϊchar����û������'+'
	std::cout << str << std::endl;

	std::vector<int> v3{ 1,2,3,4,5,6,7 };
	//��һ������������һ�������ķ�Χ����������ʾҪ�Ƚϵ��Ǹ�����
	//����һ����������Χ��ָ����Ԫ�ص�����������˳��һһ��Ӧ,�ͷ���1,�ٶ�������������ǰ��һ������ʵ���Ͽ��Աȵ�һ��������ȷ���ķ�Χ����
	std::cout << std::equal(v1.begin(), v1.end(), v3.begin()) << std::endl;

	system("pause");

	return 0;
}