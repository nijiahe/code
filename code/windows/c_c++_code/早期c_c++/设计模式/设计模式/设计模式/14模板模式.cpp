#include<iostream>
#include <vector>
#include <string>
using namespace std;
/*ģ�巽��ģʽ��ģ�巽��ģʽ׼��һ�������࣬
�������߼��Ծ��巽���Լ����幹���ӵ���ʽʵ�֣�
Ȼ������һЩ���󷽷�����ʹ����ʵ��ʣ����߼���
��ͬ����������Բ�ͬ�ķ�ʽʵ����Щ���󷽷���
�Ӷ���ʣ����߼��в�ͬ��ʵ�֡����ƶ�һ�������߼���ܣ�
�����߼���ϸ���������������ȥʵ�֡�*/

/*��һ�����ô󲿷ֿ�ܵ������,Ȼ����Ӽ������󷽷�,���ڹ��첻ͬ������,����ʵ������ǩʽ����*/
/*����ʵ�ֱ��ػ�,���ڲ�ͬ�ĵ�����Ӳ�ͬ�����Է���*/
class AbstractClass
{
public:
	void Show()
	{
		cout << "����" << GetName() << endl;
	}
protected:
	virtual string GetName() = 0;
};

class Naruto : public AbstractClass
{
protected:
	virtual string GetName()
	{
		return "��Ӱʷ����˧������Ŀ---һ������naruto";
	}
};

class OnePice : public AbstractClass
{
protected:
	virtual string GetName()
	{
		return "�����޶����Ĵ���---·��";
	}
};

//�ͻ���
int mainN()
{
	Naruto* man = new Naruto();
	man->Show();

	OnePice* man2 = new OnePice();
	man2->Show();

	cin.get();
	return 0;
}
