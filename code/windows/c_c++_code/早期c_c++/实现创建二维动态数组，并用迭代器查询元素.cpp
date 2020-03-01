#include<iostream>
#include<vector>

void main()
{
	using std::vector;
	vector<int>in1;
	in1.push_back(1);
	in1.push_back(2);

	vector<int>in2;
	in2.push_back(1);
	in2.push_back(2);
	in2.push_back(3);
	
	vector<int>in3;
	in3.push_back(1);
	in3.push_back(2);
	in3.push_back(3);
	in3.push_back(4);

	vector<vector<int>>ain;
	ain.push_back(in1);
	ain.push_back(in2);
	ain.push_back(in3);

	vector<vector<int>>::iterator ibegin1, iend1;
	ibegin1 = ain.begin();
	iend1 = ain.end();
	for (; ibegin1 != iend1; ibegin1++)
	{
		vector<int>::iterator ibegin2, iend2;
		ibegin2 = (*ibegin1).begin();
		iend2 = (*ibegin1).end();
		for (; ibegin2 != iend2; ibegin2++)
		{
			std::cout << *ibegin2 << " ";
		}
		std::cout << std::endl;
	}


	std::cin.get();
}