#include <iostream>
#include <string>
using namespace std;
//ԭ��ģʽ����̬�����ӻ���ٲ�Ʒ�࣬
//��Ʒ�಻��Ҫ�ǵ����κ�����ȷ���ĵȼ��ṹ��
//ԭʼģ��ģʽ�������κεĵȼ��ṹ��
//ȱ����ÿһ���඼�����䱸һ����¡������

class Resume
{
private:
	string name, sex, age, timeArea, company;
public:
	Resume(string s)
	{
		name = s;
	}
	void setPersonalInfo(string s, string a)
	{
		sex = s;
		age = a;
	}
	void setWorkExperience(string t, string c)
	{
		timeArea = t;
		company = c;
	}
	void display()
	{
		cout << name << "  " << sex << "  " << age << endl;
		cout << "��������:  " << timeArea << "  " << company << endl << endl;

	}
	Resume *clone()
	{
		Resume *b;
		b = new Resume(name);
		b->setPersonalInfo(sex, age);
		b->setWorkExperience(timeArea, company);
		return b;
	}
};


int mainS()
{
	Resume *r = new Resume("�����");
	r->setPersonalInfo("��", "30");
	r->setWorkExperience("2007-2010", "���о���");
	r->display();


	Resume *r2 = r->clone();
	r2->setWorkExperience("2003-2007", "������");

	r->display();
	r2->display();

	cin.get();
	return 0;
}