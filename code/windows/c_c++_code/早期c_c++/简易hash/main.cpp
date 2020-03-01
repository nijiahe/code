#include<iostream>
#include"Hash.h"
#include"Hash.cpp"
#include"hashnode.h"
#include<algorithm>
#include<vector>

using namespace std;

void main()
{
	Hash<int> hash1;
	cout << hash1.indexlong << endl;
	cout << "*****************" << endl;
	int str[] = { 5,8,9,2,5,8,45,351,87 };
	hash1.init(str);
	hashnode<int>* node=hash1.find(351);
	vector<int>::iterator ibegin = node->dataptr.begin();
	vector<int>::iterator iend = node->dataptr.end();
	while (ibegin != iend)
	{
		cout << *ibegin << endl;
		ibegin++;
	}
	cin.get();
}