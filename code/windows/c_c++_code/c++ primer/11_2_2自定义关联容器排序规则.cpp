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
#include <map>
#include <set>

int main12_2_2()
{
	//ע:����������������Լ��ƶ�Ԫ�رȽϷ�������������˳��,Ĭ������±�׼��ʹ��'<'���ȽϹؼ���
	std::multiset<int, bool(*)(int, int)> set([](int i, int j) {return i > j; });//�Զ���С�ڵĹ�����������������

	system("pause");
	return 0;
}