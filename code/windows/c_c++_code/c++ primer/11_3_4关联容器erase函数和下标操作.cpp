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
#include <utility>


int main11_3_4()
{
	std::map<std::string, int> map{ {"a",2},{"bb",5},{"cc",9} };
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair) 
	{std::cout << "Key:" << pair.first << ",Value:" << pair.second << std::endl; });
	//erase��������ɾ�����Ĺؼ��ֵ�����,���ڲ��ظ���������,��ֵ����0��1
	int count = map.erase("cc");
	std::cout << "The cc has been removed,the count is " << count << std::endl;
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair)
	{std::cout << "Key:" << pair.first << ",Value:" << pair.second << std::endl; });

	/*��map���±���������¹���:
	1.Ѱը���±��Ӧ�Ĺؼ���key
	2.���ҵ�,���ش˹ؼ��ֶ�Ӧ��value
	3.��δ�ҵ�,����²���������һ���ؼ���key��Ϊ��Ԫ��
	*/

	system("pause");
	return 0;
}