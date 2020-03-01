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
	//boolalpha和noboolalpha控制bool值输出的样式
	std::cout << true << " " << false << std::boolalpha << " " << true << " " << false << std::noboolalpha << std::endl;

	//控制整形进制的输出:oct hex dec,通过showbase,打印十六进制时会加上0x,八进制时会加上0，通过noshowbase恢复原样
	//std::cout << 0x20 << std::endl;
	std::cout << std::showbase << std::hex << 64 << std::dec << std::noshowbase << std::endl;

	//通过cout.precision()返回当前浮点数精度,cout.precision(10)将精度设置为10,或者调用setprecision(3)来设置精度
	std::cout << std::cout.precision() << std::ends << sqrt(2.0) << std::endl;
	std::cout.precision(10);
	std::cout << sqrt(2.0) << std::ends << std::setprecision(3) << sqrt(2.0) << std::endl;

	//指定浮点数计数法...要用的时候在查

	//输出补白
	/*
	setw:指定下一个数字或者字符串值的最小空间
	left:指定左对齐输出
	right:指定右对齐输出
	internal:控制-号位置,使其符号在左,数字在右,中间用空格填充
	setfill:指定一个字符代替空白来填充
	*/
	int i = -16;
	double d = 3.14159;
	//补白第一列,共占12个空间
	std::cout << "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//补白第一列,左对齐所有列
	std::cout << std::left
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::right;//还原
	//补白第一列,右对齐所有列
	std::cout << std::right
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//补白第一列,但补在内部
	std::cout << std::internal
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';
	//补白第一列,用#填充
	std::cout << std::setfill('#')
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::setfill(' ');//还原

	

	system("pause");
	return 0;
}