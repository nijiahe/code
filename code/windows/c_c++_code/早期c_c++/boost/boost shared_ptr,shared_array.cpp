#include<iostream>
#include<boost/shared_array.hpp>
#include<boost/shared_ptr.hpp>
#include<vector>
#include<algorithm>
#include<boost/function.hpp>
#include<boost/weak_ptr.hpp>
#include<Windows.h>


//shared_ptr,�������Կ���������ָ��
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

//shared_array����ָ������
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
	sh->reset();//ָ�������,�ͷ��ڴ�
	std::cout << "ָ��ִ���ͷ�" << endl;
	return 0;
}

DWORD WINAPI print(LPVOID p)
{

	boost::weak_ptr<int > * pw = static_cast<boost::weak_ptr<int > *>(p);
	boost::shared_ptr<int > sh = pw->lock();//�����������ͷ�
	Sleep(5000);
	if (sh)
	{
		std::cout << *sh << endl;
	}
	else
	{
		std::cout << "ָ���Ѿ����ͷ�" << endl;

	}

	return 0;
}
/*weak_ptrֻ����shared_ptr����ʼ��,��ʼ����ֻ�ṩһ�����õķ���lock()*/
/*weak_ptr��lock����shared_ptr������*/
void mainM()
{
	boost::shared_ptr<int> sh(new int(99));
	boost::weak_ptr<int > pw(sh);
	HANDLE threads[2];
	threads[0] = CreateThread(0, 0, reset, &sh, 0, 0);//����һ���߳�
	threads[1] = CreateThread(0, 0, print, &pw, 0, 0);
	Sleep(1000);



	WaitForMultipleObjects(2, threads, TRUE, INFINITE);//�ȴ��߳̽���

	cin.get();


}