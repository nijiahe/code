#include <iostream>
#include<array>
#include<vector>

#include"myarray.h"
#include"myarray.cpp"

using namespace std;

int main()
{
	myarray<int, 9> my1;//���캯����֤
	myarray<int, 9> my2 = my1;//����������֤
	my1.init(3, 2, 3, 4);//��ʼ��������֤,��һ������������Ҫ���뼸������
	my1.showmyarray();//showmyarray��֤
	my1.revise(3, 10);
	my1.revise(9, 100);
	my1.showmyarray();
	cin.get();
	return 0;
}

