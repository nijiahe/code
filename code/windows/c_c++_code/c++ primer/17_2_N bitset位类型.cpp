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

int main17_2_N()
{
	std::bitset<32> bit1(1U);//32λ��bitset
	std::bitset<32> bit2(0xbeef);
	std::bitset<32> bit3("1100");//bit3Ϊ000000...001100
	std::string str("110011111000011010");
	std::bitset<32> bit4(str,1,4);//��str[1]��ʼ�������ĸ��ַ�,bit4Ϊ0000...1101
	std::bitset<32> bit5(str,str.size()-4);//ʹ��str������ĸ��ַ�,bit5Ϊ0000....1010


	system("pause");
	return 0;
}