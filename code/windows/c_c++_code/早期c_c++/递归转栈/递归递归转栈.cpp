#include<iostream>
#include<stack>

using namespace std;

int add(int num)
{
	return num;
}

struct datas
{
	int num;
	int(*p)(int);
};

int print(int num)
{
	stack<datas> mystack;
	int res = 0;
AAA:
	if (num > 0)
	{
		datas data1;
		mystack.push(data1);
		data1.num = num;
		data1.p = add;
		while (!mystack.empty())
		{
			datas temp = mystack.top();
			res+=data1.p(data1.num);
			mystack.pop();
		}
		num--;
		goto AAA;
	}
	return res;

}


void main()
{
	cout << print(10) << endl;






	cin.get();
}