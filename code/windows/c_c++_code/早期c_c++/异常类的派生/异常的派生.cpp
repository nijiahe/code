#include<iostream>
#include <string>

using namespace std;

class box   //������
{
public:
	class wrong 
	{
	public:
		virtual void show()
		{
			cout << "wrong" << endl;
		}
	};
	class big:public wrong
	{
	public:
		void show()
		{
			cout << "big wrong" << endl;
		}
	};
	class small :public wrong
	{
	public:
		void show()
		{
			cout << "small wrong" << endl;
		}
	};
	box(int data) 
	{
		cout << "��ʼ����" << endl;
		if (data ==0)
		{
			zero z1(22);
			z1.errorcode = 212;
			throw z1;
		} 
		else if ( data<100)
		{
			throw small();
		}
		else  if (data>10000)
		{
			throw big();
		}
		else if (data>100 && data<10000)
		{
			a = data;
		}
		else
		{
			throw wrong{};
		}	
	}
    int  gettiji()
	{
		 return  a*a*a;
	}
	class zero/*�׳�zero��ʱ��Ҳ���׳�small,����zere�����൱��Ҳ�׳���small����*/
	{
	public:
		int errorcode;	
		zero(int i):errorcode(i)
		{

		}
		void seterrorcode(int i)
		{
			errorcode = i;
		}
	}; 
private:
	int a;//�䳤
};

void main00()
{
	try
	{
		box newbox(-1);
	}
	catch (box::zero &zerowrong)/*���յ������Ǳ��׳�������*/
	{
		cout << "�׳���zero���е�errorcode:"<< zerowrong.errorcode << endl;
		if (zerowrong.errorcode == 22)
		{
			cout << "22�Ŵ��������峤�Ȳ�����Ϊ0";
		}
		else
		{
			cout << "��22�Ŵ��������峤�Ȳ�����Ϊ0";
		}
	}
	catch (box::big &bigwrong)
	{
		bigwrong.show();
		cout << "�����峤��̫��";
	}
	catch (box::small &smallwrong)
	{
		smallwrong.show();
		cout << "�����峤��̫��";
	}
	catch (box::wrong wrong)
	{
		wrong.show();
		cout << "δ֪�쳣";
	}
	cin.get();
}