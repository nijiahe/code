#include<iostream>
#include<vector>
static int in;
static double db;
static int anum;
using std::vector;

void run(vector<int>&ins, vector<double>&dbs)
{

}
template<typename T, typename...Args>
void run(vector<int>&ins, vector<double>&dbs,T v,Args...args)
{
	anum++;
	auto num = v;	
	if (!strcmp(typeid(num).name(),"int"))
	{
		in++; ins.push_back(v);
	}
	if (!strcmp(typeid(num).name(), "double"))
	{
		db++; dbs.push_back(v);
	}
	run(ins, dbs,args...);
}

void show(vector<int>ins, vector<double>dbs)
{
	vector<int>::iterator ibegin1, iend1;
	vector<double>::iterator ibegin2, iend2;
	ibegin1 = ins.begin();
	iend1 = ins.end();
	ibegin2 = dbs.begin();
	iend2 = dbs.end();
	for (; ibegin1 != iend1; ibegin1++)
	{
		std::cout << int(*ibegin1) << std::endl;
	}
	for (; ibegin2 != iend2; ibegin2++)
	{
		std::cout << double(*ibegin2) << std::endl;
	}
}

void main()
{
	vector<int>ins;
	vector<double>dbs;
	run(ins,dbs,1,2.2,3,4.5,5);
	std::cout << "anem=" << anum << std::endl;
	std::cout << "ins=" << in << std::endl;
	std::cout << "dbs=" << db << std::endl;
	show(ins,dbs);


	std::cin.get();
}