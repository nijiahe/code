#include<iostream>

using namespace std;

class test1
{
public:
	int test1x=1;
	virtual void show()
	{
		cout << "test1 show" << endl;
	}
	void run()
	{
		cout << test1x << endl;
	}
};
class test2:public test1
{
public:
	int test2x=2;
	void show()
	{
		cout << "test2 show" << endl;
	}
	void run()
	{
		cout << test2x << endl;
	}
};

void main()
{
	test1* tes1 = new test1;
	test1* tes2 = new test2;
	cout << typeid(tes1).name() << "  " << typeid(tes2).name() << endl;
	cout << typeid(*tes1).name() << "  " << typeid(*tes2).name() << endl;
	/*����ڸ����ж���һ���麯��,����̳��˸���,������Ҳ����һ���麯��ָ��,typeid�ͻ������麯��ָ���е�������ѡ����ȷ���๹�캯������ȡ����*/
	cout << (typeid(tes1) == typeid(tes2)) << endl;
	/*typeid������!=��==*/
	test2* tes3 = nullptr;
	tes1->run();
	/*static_cast���ǵ����ĸı�ָ��ָ�Ĵ�С,ԭ���е����������ܷ�Ӧ����չ����������������ֵ,����ȫ*/
	/*tes3 = static_cast<test2*>(tes1);/*���ַ���ǿת����������ƫ���ֽ������һ�����ֵ
	static_cast������������ʴ�С���ڴ�*/
	tes3 = dynamic_cast<test2*>(tes1);/*dynamic_cast����Ը��ݴ�����������ת�������ʵ�����,������Ϊת��Ϊ������,������,��ʵ���������
									  ����������ú���������������еĳ�Ա�ͻᱨ���Ƚϰ�ȫ
									  ��static_cast�Ļ�����������޷�����ԭ��δ���벿�ֵ��ڴ�Ĺ���,�Ƚϰ�ȫ*/
	/*cout << sizeof(*tes3) << endl;/*sizeofֻ�Ǹ���ָ��ָ�ŵĴ�С������ڴ�,�����õ��ڴ沢��һ�������ϵͳ�����*/
	tes3->run();
	/*dynamic_cast<T>()��c++����ת������͸���ĺ���,��Ҫ�ɹ�ת����Ҫ�������麯��*/
	cout << (*tes3).test2x << endl;

	std::cin.get();
}