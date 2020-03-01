#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

int mainmain10_3_3()
{
	std::vector<int> v{ 1,-1,2,-3,-5,4,-6,-1 };
	//transform�㷨:����������������һ������,ǰ����������ȷ����Χ,������������ȷ��Ŀ��λ��
	//��ÿ����Χ��Ԫ�ص��õ��ĸ�������ȷ���Ŀɵ��ö���,��������ֵд��Ŀ��λ��
	std::transform(v.begin(), v.end(), v.begin(),[](int i) {return i > 0 ? i : -i; });
	for_each(v.begin(), v.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;

	/*
	*ע:�ҵĻ��������������ǿ��Ե�
	//ע:��lambda���ʽ�г���return������⻹�б�����,��δָ������ֵ,�򷵻�ֵֻ��Ϊvoid,�����д����Ǵ����
	std::transform(v.begin(), v.end(), v.begin(), [](int i) 
	{if (i > 0)return i; else return -i; });
	for_each(v.begin(), v.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	*/

//��ϰ��:
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	int count = std::count_if(v1.begin(), v1.end(), [](std::string s)->bool { return s.size() >= 4; });
	std::cout << "There is " << count << " numbers of words compatible with the condition" << std::endl;

	int n = 5;
	auto func = [&n]()->bool {while (n > 0)--n; return n == 0 ? 1 : 0; };
	bool flag = func();
	std::cout << "Now the number n is " << n << ",and the flag is " << flag << std::endl;

	system("pause");
	return 0;
}