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


int mainmain10_4_2()
{
	/*
	��������ʹ���ǿ���ͨ����һ���������󶨵�һ������,Ȼ��ͨ�������㷨�����ж�ȡ��д������
	*/
	std::ifstream in("F:\\4.txt");
	std::istream_iterator<int> fileit(in), eof;//��������������:���ڴ����ļ�������
	//std::vector<int> v1(fileit, eof);//��һ���ļ�����һ���ļ���������Ϊһ��int������������������Χ,�Դ��������ļ�
	//std::for_each(v1.begin(), v1.end(), [](int i) {std::cout << i << std::ends; });
	//ע��:���еĶ�������ȡһ���û��,����Ҫ������������ע�͵�������һ�в�����������
	std::cout << "The sum in the stream is " << std::accumulate(fileit, eof,0) << std::endl;
	
	std::ifstream in2("F:\\4.txt");
	std::istream_iterator<int> fileit2(in2);
	std::vector<int> v2(fileit2, eof);
	std::ostream_iterator<int> oit(std::cout, " ");//���������������ͨ��һ�������������,���⹹�캯������������,�ڵڶ�������������һ���ַ�������
	//��ÿ��ͨ�����������ʱ,ÿ�����֮��ᱻ���ϴ��ַ���
	//ע��:��oit��++,*������û�������,��������Щ���ó������Ϊ��Ϊֱ��,ͬʱ���ĳɱ�ĵ�����Ҳ����ͨ��,��������û��--����
	std::for_each(v2.begin(), v2.end(), [&oit](int i) {*oit++ = i; });//��v2�е�ÿ��Ԫ��ͨ����������������
	
//��ϰ��:
	std::ifstream in3("F:\\2.txt");
	std::istream_iterator<std::string> initer(in3),streof;
	std::vector<std::string> strvec(initer, streof);
	std::for_each(strvec.begin(), strvec.end(), [](std::string str) {std::cout << str << std::endl; });
	std::cout << std::endl;

	std::ifstream in4("F:\\4.txt");
	std::istream_iterator<int> initer4(in4);
	//std::sort(initer4, eof);//����,��ֻ�����ڶ�ȡ�ķ����㷨,���������޸�
	std::vector<int> v4(initer4, eof);
	std::sort(v4.begin(), v4.end());
	std::ostream_iterator<int> outiter4(std::cout," ");
	std::copy(v4.begin(), v4.end(), outiter4);

	std::ifstream in5("F:\\4.txt");
	std::ofstream out5_1("F:\\5.txt");
	std::ofstream out5_2("F:\\6.txt");
	std::istream_iterator<int> in_iter5(in5),int_eof;
	std::ostream_iterator<int> odd_iter(out5_1, " ");//�������������
	std::ostream_iterator<int> even_iter(out5_2, "\n");//ż�����������
	std::for_each(in_iter5, int_eof, [&odd_iter,&even_iter](int i) {i % 2 != 0 ? *odd_iter++ = i : *even_iter++ = i; });

	system("pause");
	return 0;
}