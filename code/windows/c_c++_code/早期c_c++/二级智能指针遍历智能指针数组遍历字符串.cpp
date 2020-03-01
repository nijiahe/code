#include<iostream>
#include<vector>
#include<memory>

void main()
{
	char num[10] = "calc";
	using namespace std;
	vector<unique_ptr<char>>allptr;
	unique_ptr<char> ch0(num);
	allptr.push_back(ch0);
	system(ch0.get());
	
	std::cin.get();
}
