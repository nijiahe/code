#include<boost/array.hpp>
#include<iostream>
/*boost��*/ 
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
	myarray.at(4)=40;//��myarray[4]����Ϊ20
	{
		boost::array<int, 10>::iterator ibegin(myarray.begin()), iend(myarray.end());
		for (; ibegin != iend; ibegin++)
		{
			cout << *ibegin << " ";
		}
		cout << endl;
	}
	int* p = myarray.data();//������׵�ַ
	cout << *p << endl;
	cout << endl;
	cin.get();
}