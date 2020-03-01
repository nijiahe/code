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
#include <bitset>

#include <iomanip>

int main()
{
	//boolalpha��noboolalpha����boolֵ�������ʽ
	std::cout << true << " " << false << std::boolalpha << " " << true << " " << false << std::noboolalpha << std::endl;

	//�������ν��Ƶ����:oct hex dec,ͨ��showbase,��ӡʮ������ʱ�����0x,�˽���ʱ�����0��ͨ��noshowbase�ָ�ԭ��
	//std::cout << 0x20 << std::endl;
	std::cout << std::showbase << std::hex << 64 << std::dec << std::noshowbase << std::endl;

	//ͨ��cout.precision()���ص�ǰ����������,cout.precision(10)����������Ϊ10,���ߵ���setprecision(3)�����þ���
	std::cout << std::cout.precision() << std::ends << sqrt(2.0) << std::endl;
	std::cout.precision(10);
	std::cout << sqrt(2.0) << std::ends << std::setprecision(3) << sqrt(2.0) << std::endl;

	//ָ��������������...Ҫ�õ�ʱ���ڲ�

	//�������
	/*
	setw:ָ����һ�����ֻ����ַ���ֵ����С�ռ�
	left:ָ����������
	right:ָ���Ҷ������
	internal:����-��λ��,ʹ���������,��������,�м��ÿո����
	setfill:ָ��һ���ַ�����հ������
	*/
	int i = -16;
	double d = 3.14159;
	//���׵�һ��,��ռ12���ռ�
	std::cout << "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//���׵�һ��,�����������
	std::cout << std::left
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::right;//��ԭ
	//���׵�һ��,�Ҷ���������
	std::cout << std::right
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//���׵�һ��,�������ڲ�
	std::cout << std::internal
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//���׵�һ��,��#���
	std::cout << std::setfill('#')
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::setfill(' ');//��ԭ

	

	system("pause");
	return 0;
}