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
			cout << "����ɹ�" << endl;
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
		cout << "�߳��쳣" << endl;
	}
	catch (box::wrong)
	{
		cout << "δ֪�쳣" << endl;
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
//class box   //������
//{
//public:
//	box(int data) 
//	{
//		cout << "��ʼ����";
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
//	int a;//�䳤
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
//			cout << "22�Ŵ��������峤�Ȳ�����Ϊ0";
//	    } 
//	    else
//	    {
//			cout << "fei22�Ŵ��������峤�Ȳ�����Ϊ0";
//	    }
//		
//	}
//	catch (box::wrong)
//	{
//
//		cout << "�����峤���쳣";
//	}
//	catch (box::big)
//	{
//
//		cout << "�����峤��̫��";
//	}
//	catch (box::small)
//	{
//
//		cout << "�����峤��taiduan";
//	}
//
//	cin.get();
//
//}