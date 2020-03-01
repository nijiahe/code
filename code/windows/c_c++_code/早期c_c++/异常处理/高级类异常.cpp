#include<iostream>
#include<string>

using namespace std;

class box
{
private:
	int sidelong;
public:
	box(int data)
	{
		if (data <= 0|| data > 10000)
		{
			throw sidewrong();
		}
		else if(data>0&&data<=10000)
		{
			sidelong = data;
			cout << "构造成功" << endl;
		}
		else
		{
			throw wrong();
		}
	}
	class sidewrong {};
	class wrong {};
};


void main()
{
	try
	{
		box(3);
	}
	catch (box::sidewrong)
	{
		cout << "边长异常" << endl;
	}
	catch (box::wrong)
	{
		cout << "未知异常" << endl;
	}

	cin.get();
}


















//
//#include<iostream>
//#include <string>
//
//
//using namespace std;
//
//
//
//class box   //正方体
//{
//public:
//	box(int data) 
//	{
//		cout << "开始构造";
//
//		if (data ==0)
//		{
//			zero z1;
//			z1.errorcode = 212;
//			throw z1;
//		} 
//		else if ( data >0 && data<100)
//		{
//			throw small();
//		}
//		else  if (data>10000)
//		{
//			throw big();
//		}
//		else if (data>100 && data<10000)
//		{
//			a = data;
//		}
//		else
//		{
//			throw wrong{};
//		}
//		
//		
//	}
//
//
//    int  gettiji()
//	{
//
//
//		 return  a*a*a;
//	}
//
//	class zero
//	{
//	public:
//		int errorcode;
//	
//	}; 
//	class wrong{};
//	class big{};
//	class small{};
//private:
//	int a;//变长
//
//
//
//
//};
//
//void main()
//{
//
//	try
//	{
//		box newbox(0);
//
//	}
//	catch (box::zero w)
//	{
//	    if (w.errorcode==22)
//	    {
//			cout << "22号错误正方体长度不可以为0";
//	    } 
//	    else
//	    {
//			cout << "fei22号错误正方体长度不可以为0";
//	    }
//		
//	}
//	catch (box::wrong)
//	{
//
//		cout << "正方体长度异常";
//	}
//	catch (box::big)
//	{
//
//		cout << "正方体长度太长";
//	}
//	catch (box::small)
//	{
//
//		cout << "正方体长度taiduan";
//	}
//
//	cin.get();
//
//}