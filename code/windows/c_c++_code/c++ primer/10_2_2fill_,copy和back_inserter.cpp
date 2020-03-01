#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_2()
{
	std::vector<int> v1{ 1,2,3,4,5,6 };
	for (auto i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill(v1.begin(), v1.end(), 3);//std::fill�����������������Ա�ʾfill�ķ�Χ�������������ñ�ʾfill��ֵ
	for (auto i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;

	std::vector<int> v2{ 1,2,3,4,5,6 };
	for (auto i : v2)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill_n(v2.begin(), v2.size()-1, 3);//std::fill_n����һ����������һ��fill���������Ա�ʾ��Χ�������������ñ�ʾfill��ֵ
	for (auto i : v2)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//���������
	//������������ֵ�൱�ڵ���pushback()������ֵ����������
	//����back_insert_iterator��++��--��������û������
	std::vector<int> v3;
	std::back_insert_iterator<std::vector<int> > bi = std::back_inserter(v3);
	std::fill_n(bi, 10, 6);//Ϊ�˲����������ֵ�൱���������ڲ���Ԫ��
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//copy�㷨,����3������,������������equalһ����ǰ������ʾһ����Χ����ǰ����ȷ���ķ�Χ����������������ָʾ��������λ��
	std::copy(v1.begin(), v1.end(), v3.begin());
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//replace�㷨:�����ĸ�������ǰ����������ȷ�Ϸ�Χ������Χ�����еĵ�����������Ϊ���ĸ�����
	std::replace(v3.begin(), v3.end(),6,9 );
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//replace_copy�㷨:����5�����������㷨����һ��������ȷ���ķ�Χ�ڵ����е��ĸ������滻Ϊ����������������뵽�������������ṩ�Ĳ����������
	//�������������ǲ��ı䲻�ı�ԭ�е����������滻������з�����������
	std::vector<int> v4;
	std::replace_copy(v3.begin(), v3.end(), std::back_inserter(v4), 9, 7);
	for (auto i : v4)
		std::cout << i << std::ends;
	std::cout << std::endl;

//��ϰ��:
	std::vector<int> v5{ 1,2,3,4,5,6,7,8,9 };
	for (int i : v5)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill_n(v5.begin(), v5.size(), 0);
	for (int i : v5)
		std::cout << i << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}