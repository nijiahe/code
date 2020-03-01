#include<iostream>
#include<boost/unordered_set.hpp>
#include<string>
#include<algorithm>

using namespace std;

void mainO()
{
	boost::unordered_set<std::string> unorderedset;
	unorderedset.insert("a");
	unorderedset.insert("b");
	unorderedset.insert("c");
	unorderedset.insert("aa");
	unorderedset.insert("ab");
	unorderedset.insert("bc");
	for_each(unorderedset.begin(), unorderedset.end(), [] (string x){cout << x << endl; });

	cin.get();
}