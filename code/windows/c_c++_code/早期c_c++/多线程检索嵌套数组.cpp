#include<iostream>
#include<vector>
#include<thread>
#include<Windows.h>
#include<array>
using namespace std;
//若传的参数是一个vector<int>类型的数组，用run2
//若传的参数是一个用vector<vector<int>>::iterator创建出来的类的实例(当作指针使用),用run
void run(vector<vector<int>>::iterator it)
{
	vector<int>::iterator this_ibegin, this_iend;
	this_ibegin = it->begin();
	this_iend = it->end();
	for (; this_ibegin != this_iend; this_ibegin++)
	{
		std::cout << *this_ibegin<<" ";
	}
	std::cout << std::endl;
}
void run2(vector<int> vec)
{
	vector<int>::iterator this_ibegin, this_iend;
	this_ibegin = vec.begin();
	this_iend = vec.end();
	for (; this_ibegin != this_iend; this_ibegin++)
	{
		std::cout << *this_ibegin << " ";
	}
	std::cout << std::endl;
}

void main01()
{
	vector<int> vec1;
	for (int i = 0; i < 1; i++)
	{
		vec1.push_back(i);
	}
	vector<int> vec2;
	for (int i = 0; i < 2; i++)
	{
		vec2.push_back(i);
	}
	vector<int> vec3;
	for (int i = 0; i < 3; i++)
	{
		vec3.push_back(i);
	}
	vector<vector<int>> allvec;
	allvec.push_back(vec1);
	allvec.push_back(vec2);
	allvec.push_back(vec3);
	vector<vector<int>>::iterator ibegin1, iend1,ibegin2, iend2;
	//ibegin1, iend1,ibegin2, iend2是类的实例，并不是单纯的指针，类的内部通过重载操作符的方式将*ibegin1等得以实现
	ibegin1 = allvec.begin();
	iend1 = allvec.end();
	ibegin2 = allvec.begin();
	iend2 = allvec.end();
	vector<std::thread*> threads;	
	for (; ibegin1!= iend1; ibegin1++)
	{
		Sleep(500);
		threads.push_back(new std::thread(run2,*ibegin1));
	}
	for (auto th : threads)
	{
		th->join();
	}
	std::cin.get();
}

/*void find(array<int,1000> ar,int n)
{
	static int count = -1;
	for (int i = 0; i < ar.size(); i++)
	{
		count++;
		if (ar[i] == n)
		{
			int n = count / 1000;
			int m = count - n * 1000;
			std::cout << "位于数组" << n << "的[" << m << "]" << std::endl;
		}
	}
}*/
int find(array<int, 1000> ar, int num)
{
	static int res = 0;
	static int count = -1;
	count++;
	int min = 0;
	int max = ar.size() - 1;
	int middle = max / 2;
	if (res == 1)
	{
		return 0;
	}
	while (min <= max)
	{
		if (num == ar[middle])
		{
			res++;
			std::cout << "["<<count<<"]";
			std::cout << "[" << middle << "]" << std::endl;
			return 1;
		}
		if (num > ar[middle])
		{
			min = middle + 1;
			middle = (min + max) / 2;
		}
		if (num < ar[middle])
		{
			max = middle - 1;
			middle = (min + max) / 2;
		}
	}
	return 0;
}
void main()
{
	array<int, 1000> ar1;
	array<int, 1000>ar2;
	array<int, 1000>ar3;
	array<array<int,1000>, 3>allar;
	for (int i = 0; i < ar1.size(); i++)
	{
		ar1[i] = i;//0-999
	}
	for (int i = 0; i < ar2.size(); i++)
	{
		ar2[i] = i+1000;//1000-1999
	}
	for (int i = 0; i < ar3.size(); i++)
	{
		ar3[i] = i+2000;//2000-2999
	}
	allar[0] = ar1;
	allar[1] = ar2;
	allar[2] = ar3;
	vector<std::thread*>threads;
	for (int i = 0; i < allar.size(); i++)
	{
		Sleep(1000);
		threads.push_back(new std::thread(find,allar[i],0));
	}
	for (int i = 0; i < allar.size(); i++)
	{
		threads[i]->join();
	}
	std::cin.get();
}

