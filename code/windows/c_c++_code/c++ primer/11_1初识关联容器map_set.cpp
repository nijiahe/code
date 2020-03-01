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

int main11_1()
{
//¡∑œ∞Ã‚:
	std::map<std::string, int> map;
	std::set<std::string> set{ "the","a","an","and","but" };
	std::string word;
	while (std::cin >> word)
	{
		std::for_each(word.begin(), word.end(), [](char &ch) {ch = tolower(ch); });
		word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
		if (std::find(set.begin(), set.end(), word) == set.end())
			++map[word];
	}
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> map_pair) 
	{std::cout << "The word is " << map_pair.first << ", and the count is " << map_pair.second << std::endl; });


	system("pause");
	return 0;
}