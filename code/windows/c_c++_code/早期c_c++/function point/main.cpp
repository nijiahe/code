#include<iostream>

using namespace std;

int add(int num1, int num2)
{
	return num1 + num2;
}
void main01()
{
	int(*p)(int, int) = add;
	cout << p(1, 2) << endl;
	/*��������ʾ�Ķ��Ǵ洢��add�����ĺ���ָ��ĵ�ַ,����������*/
	cout << p << endl;
	cout << *****p << endl;/*�������Զ���*p����Ϊp,�����û���ú����ĵ�ַ*/
	cout << &p << endl;
	cout << typeid(p).name() << endl;
	cout << typeid(***p).name() << endl;
	cout << typeid(&p).name() << endl;
	std::cin.get();
}
/*��ȡ��ͨ�����ĵ�ַ*/

class test
{
public:
	int x;
	int y;
	test(int num1,int num2):x(num1),y(num2)
	{

	}
	int add(int num1, int num2)
	{
		return num1 + num2;
	}
	int minus(int num1, int num2)
	{
		return num1 - num2;
	}
	int multy(int num1, int num2)
	{
		return num1 * num2;
	}
	int devide(int num1, int num2)
	{
		return num1 / num2;
	}
	int show()
	{
		return x + y;
	}
};
/*��ȡ��Ա�����еĵ�ַ������*/
void main02()
{
	test tes1(2, 3);
	int(test::*p)(int, int) = &test::add;/*����ָ��ָ�����еĺ���*/
	int(test::*ptr)() = &test::show;/*����ָ��ָ�����еĺ���*/
	cout << (tes1.*p)(3, 5) << endl;//�������к�������������ʵ��,��Ϊ���еĺ������Ե������еĳ�Ա����,������ʵ���ᵼ�º������������ڱȱ�����,
	cout << (tes1.*ptr)() << endl;
	std::cin.get();
}
typedef int(test::*P)(int, int);/*��������,��int(test::*)(int,int)���ͺ���ָ�붨��ΪP*/

void main()
{
	test tes1(3, 2);
	P func[4] = { &test::add,&test::minus, &test::multy, &test::devide };/*����һ������ָ������,�����е�ÿһ��Ԫ��ָ�����еĺ���*/
	int(test::*ptr[4])(int, int)= { &test::add,&test::minus, &test::multy, &test::devide };
	for (int i = 0; i < 4; i++)/*ѭ�����ε��üӼ��˳�*/
	{
		cout << (tes1.*ptr[i])(9, 5) << endl;
	}
	int(test::**p)(int, int) = ptr;/*ָ�����Ա����ָ���ָ��*/
	for (; p < ptr + 4; p++)
	{
		cout << (tes1.**p)(9,5) << endl;
	}
	std::cin.get();
}
