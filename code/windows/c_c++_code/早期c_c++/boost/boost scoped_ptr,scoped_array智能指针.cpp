#include<iostream>
#include<boost/scoped_ptr.hpp>
#include<boost/scoped_array.hpp>

using namespace std;

void mainI()
{
	boost::scoped_ptr<int> ptr(new int);
	*ptr = 12;
	//ptr.get()���ص���ptr����ĵ�ַ
	cout << *ptr.get() << endl;
	ptr.reset(new int);//���¸�ֵ,ɾ��ǰһ����ַ
	*ptr.get() = 3;
	//boost::scoped_ptr<int> ptr2(ptr);����������˽��,�޷�����,���Ա�֤��������ָ�봴����ָ�벻���ظ�ɾ��
	cout << *ptr.get() << endl;

	cin.get();
}
//����ָ������
void mainJ()
{
	boost::scoped_array<int> ptr(new int[10]);
	for (int i = 0; i < 10; i++)
	{
		ptr[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << ptr[i] << " ";
	}
	cin.get();
}