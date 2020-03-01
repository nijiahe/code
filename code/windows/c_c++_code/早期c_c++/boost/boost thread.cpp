#include <iostream>
#include <vector>
#include<algorithm>
#include<boost/thread.hpp>
#include <windows.h>

using namespace std;

void wait(int sec)//�ȴ�sec��
{
	//this_thread���ʵ�ǰ�߳�
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

void threadB()//������̱��ж�,���interrupted
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
	boost::thread th(threadB);//�̳߳�
	wait(3);
	th.interrupt();//��ǰ�����߳�
	th.join();

	cin.get();
}