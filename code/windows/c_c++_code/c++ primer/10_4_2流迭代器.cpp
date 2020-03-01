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
	流迭代器使我们可以通过将一个迭代器绑定到一个流上,然后通过泛型算法从流中读取和写入数据
	*/
	std::ifstream in("F:\\4.txt");
	std::istream_iterator<int> fileit(in), eof;//流迭代器的妙用:用于创建文件结束符
	//std::vector<int> v1(fileit, eof);//以一个文件流和一个文件结束符流为一个int容器的两个迭代器范围,以此来创建文件
	//std::for_each(v1.begin(), v1.end(), [](int i) {std::cout << i << std::ends; });
	//注意:流中的东西被读取一遍就没了,所以要把上面两行先注释掉下面这一行才能正常运作
	std::cout << "The sum in the stream is " << std::accumulate(fileit, eof,0) << std::endl;
	
	std::ifstream in2("F:\\4.txt");
	std::istream_iterator<int> fileit2(in2);
	std::vector<int> v2(fileit2, eof);
	std::ostream_iterator<int> oit(std::cout, " ");//输出流迭代器可以通过一个输出流来创建,此外构造函数有重载类型,在第二个参数处接受一个字符串类型
	//则每次通过迭代器输出时,每个输出之后会被加上此字符串
	//注意:对oit的++,*操作是没有意义的,但加上这些会让程序的行为更为直观,同时若改成别的迭代器也可以通用,流迭代器没有--操作
	std::for_each(v2.begin(), v2.end(), [&oit](int i) {*oit++ = i; });//将v2中的每个元素通过输出流迭代器输出
	
//练习题:
	std::ifstream in3("F:\\2.txt");
	std::istream_iterator<std::string> initer(in3),streof;
	std::vector<std::string> strvec(initer, streof);
	std::for_each(strvec.begin(), strvec.end(), [](std::string str) {std::cout << str << std::endl; });
	std::cout << std::endl;

	std::ifstream in4("F:\\4.txt");
	std::istream_iterator<int> initer4(in4);
	//std::sort(initer4, eof);//错误,流只能用于读取的泛函算法,不能用于修改
	std::vector<int> v4(initer4, eof);
	std::sort(v4.begin(), v4.end());
	std::ostream_iterator<int> outiter4(std::cout," ");
	std::copy(v4.begin(), v4.end(), outiter4);

	std::ifstream in5("F:\\4.txt");
	std::ofstream out5_1("F:\\5.txt");
	std::ofstream out5_2("F:\\6.txt");
	std::istream_iterator<int> in_iter5(in5),int_eof;
	std::ostream_iterator<int> odd_iter(out5_1, " ");//奇数输出迭代器
	std::ostream_iterator<int> even_iter(out5_2, "\n");//偶数输出迭代器
	std::for_each(in_iter5, int_eof, [&odd_iter,&even_iter](int i) {i % 2 != 0 ? *odd_iter++ = i : *even_iter++ = i; });

	system("pause");
	return 0;
}