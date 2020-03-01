#include <iostream>
#include<array>
#include<vector>

#include"myarray.h"
#include"myarray.cpp"

using namespace std;

int main()
{
	myarray<int, 9> my1;//构造函数验证
	myarray<int, 9> my2 = my1;//拷贝函数验证
	my1.init(3, 2, 3, 4);//初始化函数验证,第一个函数传的是要传入几个数据
	my1.showmyarray();//showmyarray验证
	my1.revise(3, 10);
	my1.revise(9, 100);
	my1.showmyarray();
	cin.get();
	return 0;
}

