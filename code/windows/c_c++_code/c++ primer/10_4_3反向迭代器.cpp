#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>


int main10_4_3()
{
	//���������ֻ�����ڼ���++����--����������,��forward_list(��������)������֧�ַ��������
	std::string str("FIRST,MIDDLE,LAST");
	std::string::reverse_iterator str_riter = std::find(str.rbegin(), str.rend(), ',');
	std::cout << std::string(str.rbegin(), str_riter) << std::endl;
	//reverse_iterator(���������)�г�Ա����base,���Խ�����������ĵ���˳���Ϊ��
	std::cout << std::string(str_riter.base(), str.end()) << std::endl;

//��ϰ��:
	std::vector<int> v1{ 1,3,5,7,0,6,1,3,9,8,1,3,0,4,8 };
	std::for_each(v1.rbegin(), v1.rend(), [](int i) {std::cout << i << std::ends; }); std::cout << std::endl;

	for (std::vector<int>::iterator iter = v1.end(); iter != v1.begin(); )
	{
		std::cout << *(--iter) << std::ends;
	}
	std::cout << std::endl;

	std::vector<int>::reverse_iterator riter = std::find(v1.rbegin(), v1.rend(), 0);
	std::cout << std::distance(riter,v1.rend()) << std::endl;

	std::vector<int> v2{ 11,22,33,44,55,66,77,88,99,1010,1111 };
	std::list<int> list;
	std::copy(v2.rbegin() + 3, v2.rend() - 3, std::back_inserter(list));//��ԭ����ֱ����list��ʼ�����캯����,github���Ǹ�����back_inserter���Ը��ܻع���ѧ֪ʶ
	std::for_each(list.begin(), list.end(), [](int i) {std::cout << i << std::ends; });

	std::cout << std::endl;

	system("pause");
	return 0;
}