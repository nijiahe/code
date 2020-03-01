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
	std::bitset<32> bit1(1U);//32位的bitset
	std::bitset<32> bit2(0xbeef);
	std::bitset<32> bit3("1100");//bit3为000000...001100
	std::string str("110011111000011010");
	std::bitset<32> bit4(str,1,4);//从str[1]开始的往后四个字符,bit4为0000...1101
	std::bitset<32> bit5(str,str.size()-4);//使用str的最后四个字符,bit5为0000....1010


	system("pause");
	return 0;
}