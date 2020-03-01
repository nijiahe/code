#include <iostream>
#include <string>
#include <list>
using namespace std;

//�۲���ģʽ���۲���ģʽ������һ��һ�Ӷ��������ϵ��
//�ö���۲��߶���ͬʱ����ĳһ���������
//������������״̬�Ϸ����仯ʱ����֪ͨ���й۲��߶���
//ʹ�����ܹ��Զ������Լ���

//�����ߵ��࣬�������еĹ۲��ߣ����ӻ���ɾ����������Ϣ���ù۲��ߴ���
//�۲��ߵ�����Ҫ������Ϣ������

/*������ģʽͨ������һ���۲���,��N����֪ͨ��,�۲�����洢��֪ͨ�ߵ�����ĵ�ַ,��֪ͨ����洢�۲��ߵĵ�ַ,�������ķ�ʽʵ����Ϣ����*/
/*�����Ավ�ڹ���۲��ߵĽǶȽ������,��Ϊ�۲�����ӱ�֪ͨ�����*/
class Subject; //����ʹ��subject

class Observer//��֪ͨ�Ķ���ĳ���
{
protected:
	string name;
	Subject *sub;
public:
	Observer(string name, Subject *sub)//�۲��ߵ����֣� ������֪ͨ����
	{
		this->name = name;//��������
		this->sub = sub;//����˭��֪ͨ��
	}
	virtual void update() = 0;//���麯��
};

class StockObserver :public Observer //�̳У��Լ�ʵ��ˢ�º���
{//����Ʊ�ı�֪ͨ����
public:
	StockObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();//�˶��������Ϣʱ���Ķ���
};

class NBAObserver :public Observer
{//��NBA�ı�֪ͨ����
public:
	NBAObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();//�˶�����ܲ�ͬ��Ϣʱ���Ĳ�ͬ����
};

class Subject  //
{
protected:
	list<Observer*> observers;///�洢��֪ͨ���������
public:
	string action;//��Ϣ����
	virtual void attach(Observer*) = 0;//���һ����֪ͨ����
	virtual void detach(Observer*) = 0;//ɾ��һ����֪ͨ����
	virtual void notify() = 0;//ʵ�ּ����Ļ���
};


class Secretary :public Subject
{
	void attach(Observer *observer)  //����֪ͨ���б�
	{
		observers.push_back(observer);
	}
	void detach(Observer *observer)//ɾ��
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			if ((*iter) == observer)
			{
				observers.erase(iter);
			}
			++iter;
		}
	}
	void notify()  ///֪ͨ,�������ڵ�ÿ����֪ͨ�ߴ�����Ϣ
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			(*iter)->update();
			++iter;
		}
	}
};

void StockObserver::update()//��֪ͨ����洢��֪ͨ�˵�ָ��,��������֪ͨ�˵���Ϣ
{
	cout << name << " �յ���Ϣ��" << sub->action << endl;
	if (sub->action == "����������!")
	{
		cout << "�����Ϲرչ�Ʊ��װ�������湤�������ӣ�" << endl;
	}
	if (sub->action == "ȥ�Ⱦƣ�")
	{
		cout << "��������" << endl;
	}
}

void NBAObserver::update()
{
	cout << name << " �յ���Ϣ��" << sub->action << endl;
	if (sub->action == "����������!")
	{
		cout << "�����Ϲر�NBA��װ�������湤�������ӣ�" << endl;
	}

	if (sub->action == "ȥ�Ⱦƣ�")
	{
		cout << "��������" << endl;
	}
}

int mainJ()
{
	Subject *dwq = new Secretary();//��Ϣ���ӣ�����(dwq��һ���۲���)

	Observer *xs = new NBAObserver("xiaoshuai", dwq);//������Ϣ
	Observer *zy = new NBAObserver("zouyue", dwq);//(����,˭֪ͨ)
	Observer *lm = new StockObserver("limin", dwq);

	dwq->attach(xs);//���������֪ͨ����
	dwq->attach(zy);
	dwq->attach(lm);//���ӵ�����

	dwq->action = "ȥ�Է��ˣ�";
	dwq->notify();
	dwq->action = "ȥ�Ⱦƣ�";
	dwq->notify();
	cout << endl;
	dwq->action = "����������!";
	dwq->notify();
	cin.get();
	return 0;
}