#include<iostream>
#include <string>

using namespace std;

class box   //正方体
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
		cout << "开始构造" << endl;
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
	class zero/*抛出zero的时候也会抛出small,这样zere错误相当于也抛出了small错误*/
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
	int a;//变长
};

void main00()
{
	try
	{
		box newbox(-1);
	}
	catch (box::zero &zerowrong)/*接收的数据是被抛出的数据*/
	{
		cout << "抛出的zero类中的errorcode:"<< zerowrong.errorcode << endl;
		if (zerowrong.errorcode == 22)
		{
			cout << "22号错误正方体长度不可以为0";
		}
		else
		{
			cout << "非22号错误正方体长度不可以为0";
		}
	}
	catch (box::big &bigwrong)
	{
		bigwrong.show();
		cout << "正方体长度太长";
	}
	catch (box::small &smallwrong)
	{
		smallwrong.show();
		cout << "正方体长度太短";
	}
	catch (box::wrong wrong)
	{
		wrong.show();
		cout << "未知异常";
	}
	cin.get();
}