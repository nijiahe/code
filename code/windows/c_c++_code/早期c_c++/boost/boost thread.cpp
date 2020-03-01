#include <iostream>
#include <vector>
#include<algorithm>
#include<boost/thread.hpp>
#include <windows.h>

using namespace std;

void wait(int sec)//等待sec秒
{
	//this_thread访问当前线程
	boost::this_thread::sleep(boost::posix_time::seconds(sec));
}

void threadA()
{
	for (int i = 0; i< 10; i++)
	{
		wait(1);
		cout << i << endl;
	}
}

void threadB()//如果进程被中断,输出interrupted
{
	try
	{
		for (int i = 0; i< 10; i++)
		{
			wait(1);
			cout << i << endl;
		}
	}
	catch (boost::thread_interrupted &)
	{
		cout << "interrupted" << endl;
	}
}

void mainN()
{
	boost::thread th(threadB);//线程池
	wait(3);
	th.interrupt();//提前结束线程
	th.join();

	cin.get();
}