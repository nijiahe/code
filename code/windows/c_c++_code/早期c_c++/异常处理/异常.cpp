#include <iostream>
#include <string.h>
#include<array>
using namespace std;
/*����һ��������Ŵ������Ϣ*/
/*C++ͨ�������������Ķ��������ݴ�����Ϣ*/
class devwrong 
{

};
/*������Ϊ0�������쳣*/
int intdiv(int a, int b)
{
	try
	{
		if (b == 0)
		{/*�׳�һ����������,��Ҳ����throw 10*/
			throw devwrong();/*�׳�devwrong������*/
			/*�׳����ֱ�ӽ���try��������*/
			/*devwrong����Ĭ�Ϲ��캯��,����һ������*/
			cout << "aa" << endl;
		}
		return a / b;
	}
	/*catch()����һ����������*/
	catch (devwrong)/*�����������devwrong*/
	{
		cout << "�쳣,����Ϊ0" << endl;
		return -1;
	}
	
}
void main00()
{
	cout << intdiv(2, 0) << endl;
	cin.get();
}
/*�����������*/
class arraywrong
{

};

template<class T,int NUM>
T showarray(array<T,NUM> valuear,int num)
{
	try
	{
		if (NUM < num)
		{
			throw 10;//arraywrong();
		}
		return valuear[num];
	}
	catch (int)
	{
		cout << "��ѯ�������������,�������������һ��Ԫ��" << endl;
		return valuear[NUM-1];
	}

}

void main()
{
	array<int,10> ar1 = { 0,1,2,3,4,5,6,7,8,9 };
	cout << showarray<int, 10>(ar1,12);

	cin.get();
}




















/*


//��ʶ���������
class wrong  
{


};

int intdiv(int a, int b)
{

	try
	{
	  
		if (b==0)
		{
			throw 10;//�������κζ���  wrong();
		}
		int c = a / b;
		return c;


	}
	catch (int data )//������
	{
		
		cout << "�����쳣�Ѿ�����";
		return -1;

	}


}

int intdivA(int a, int b)
{

	return a / b;
}

void main01()
{

	int x, y;
	cin >> x >> y;
	try
	{
		if (y==0)
		{
			throw "������Ϊ0";
		}
		else if (x==0)
		{
			throw "����Ϊ0";
		}

	}
	catch (const char * s)
	{
		if (strcmp(s,"������Ϊ0")==0)
		{
			cout << "������Ϊ0�쳣������������";
			cin >> x >> y;

		}
		else  if (strcmp(s, "����Ϊ0") == 0)
		{
			cout << "����Ϊ0�쳣������������";
			cin >> x >> y;
		}

	}






	std::cout << intdiv(x, y);
	cin.get();
	cin.get();
	cin.get();







}*/