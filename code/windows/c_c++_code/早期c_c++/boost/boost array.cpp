#include<boost/array.hpp>
#include<iostream>
/*boost库*/ 
using namespace std;

void mainA()
{
	boost::array<int, 10 >myarray = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	{
		boost::array<int, 10>::iterator ibegin(myarray.begin()), iend(myarray.end());
		for (; ibegin != iend; ibegin++)
		{
			cout << *ibegin << " ";
		}
		cout << endl;
	}
	
	myarray[3] = 30;
	myarray.at(4)=40;//将myarray[4]更改为20
	{
		boost::array<int, 10>::iterator ibegin(myarray.begin()), iend(myarray.end());
		for (; ibegin != iend; ibegin++)
		{
			cout << *ibegin << " ";
		}
		cout << endl;
	}
	int* p = myarray.data();//数组的首地址
	cout << *p << endl;
	cout << endl;
	cin.get();
}