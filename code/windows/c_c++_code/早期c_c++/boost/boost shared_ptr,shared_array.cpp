#include<iostream>
#include<boost/shared_array.hpp>
#include<boost/shared_ptr.hpp>
#include<vector>
#include<algorithm>
#include<boost/function.hpp>
#include<boost/weak_ptr.hpp>
#include<Windows.h>


//shared_ptr,创建可以拷贝的智能指针
using namespace std;

void mainK()
{
	vector<boost::shared_ptr<int>> vec;
	boost::shared_ptr<int> p(new int(12));
	vec.push_back(p);
	vec.push_back(p);
	vec.push_back(p);
	vec.push_back(p);
	for_each(vec.begin(), vec.end(), [](boost::shared_ptr<int> ptr) {cout << *ptr.get() << endl; });

	cin.get();
}

//shared_array共享指针数组
void mainL()
{
	boost::shared_array<int> ptr(new int[10]);
	for (int i = 0; i < 10; i++)
	{
		ptr[i] = i;
	}
	boost::shared_array<int> ptr2(ptr);
	for (int i = 0; i < 10; i++)
	{
		cout << ptr2[i] << " ";
	}


	cin.get();
}


DWORD  WINAPI reset(LPVOID p)
{
	boost::shared_ptr<int > *sh = static_cast<boost::shared_ptr<int > *> (p);
	sh->reset();//指针的重置,释放内存
	std::cout << "指针执行释放" << endl;
	return 0;
}

DWORD WINAPI print(LPVOID p)
{

	boost::weak_ptr<int > * pw = static_cast<boost::weak_ptr<int > *>(p);
	boost::shared_ptr<int > sh = pw->lock();//锁定不可以释放
	Sleep(5000);
	if (sh)
	{
		std::cout << *sh << endl;
	}
	else
	{
		std::cout << "指针已经被释放" << endl;

	}

	return 0;
}
/*weak_ptr只能用shared_ptr来初始化,初始化后只提供一个有用的方法lock()*/
/*weak_ptr起到lock辅助shared_ptr的作用*/
void mainM()
{
	boost::shared_ptr<int> sh(new int(99));
	boost::weak_ptr<int > pw(sh);
	HANDLE threads[2];
	threads[0] = CreateThread(0, 0, reset, &sh, 0, 0);//创建一个线程
	threads[1] = CreateThread(0, 0, print, &pw, 0, 0);
	Sleep(1000);



	WaitForMultipleObjects(2, threads, TRUE, INFINITE);//等待线程结束

	cin.get();


}