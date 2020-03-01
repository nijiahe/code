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

std::string *mystrstr(const std::string str1, const std::string str2)
{
	std::string *str = new std::string(str1 + str2);
	return str;
}

char * transformCinToStr()
{
	int num = 0;
	std::string word;
	std::string sentence;
	while (std::cin >> word)
		sentence += word;
	char * ret = new char[sentence.size() + 1];
	strcpy_s(ret, sentence.size() + 1, sentence.c_str());
	return ret;
}

int main12_2_1()
{
	//ͨ��new��������,���ص���ָ������ͷ��ָ��
	int* arr = new int[42];
	//new����֧�ֲ����б��ʼ��
	int* arr2 = new int[3]{1,2,3};
	std::cout << arr2[0] << arr2[1] << arr2[2] << std::endl;
	//ɾ����̬����Ĳ���,ɾ��ʱ�ײ�Ϊ����ɾ��
	delete[]arr;
	delete[]arr2;
	//��׼���ṩ��һ����unique_ptr����̬����ķ���,���ö�̬��������ʼ��unique_ptr,��֧���±����
	std::unique_ptr<int[]> uptr(new int[3]{4,5,6});
	std::cout << uptr[0] << uptr[1] << uptr[2] << std::endl;
	//release��reset��Ա���������delete[]��ɾ������ָ��Ķ�̬����
	uptr.release();
	//����shared_ptr������̬����,��Ҫ�����Լ��趨��delete,�����ɶ�̬�����ʼ����shared_ptrδ�����±������,������ָ�뱾��֧���±�����
	//������shared_ptr������̬����,����ʷ�ʽ��unique_ptr����������ƫ��
	std::shared_ptr<int> sptr(new int[3]{7,8,9}, [](int *p) {delete[]p; });
	for (int i = 0; i < 3; i++)
		std::cout << *(sptr.get() + i) << std::ends;
	std::cout << std::endl;

//��ϰ��:
	std::string* str = mystrstr("hello,", "world");
	std::cout << *str << std::endl;
	delete str;

	char * str2 = transformCinToStr();
	std::cout << str2 << std::endl;
	delete[]str2;

	system("pause");
	return 0;
}
