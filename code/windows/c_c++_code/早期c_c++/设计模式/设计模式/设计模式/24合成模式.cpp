#include <iostream>
#include <vector>
#include <string>
using namespace std;
//�ϳ�ģʽ���ϳ�ģʽ��������֯�����ṹ�У������������������벿�ֵĹ�ϵ��
//�ϳ�ģʽ����һ�������������ṹ��ģʽ���ϳ�ģʽ�Ѳ���������Ĺ�ϵ�����ṹ��ʾ������
//�ϳ�ģʽʹ�ÿͻ��˰�һ���������ĳɷֶ���������Ǹ��϶��ɵĺϳɶ���ͬ�ȿ�����


/*С���ı�����һ��leaf,����С����display��leaf��display,ֱ�Ӵ�ӡ С��
Сǿ��Ȼ
С���ı�����һ��Componsite,��һ�������,��ӡС���൱��Ҫ����Conposite�Ĵ�ӡ,��һ���ݹ����*/

/*ʵ������Ĳ�θ�*/
class Component//����
{
public:
	string name;
	Component(string name)
	{
		this->name = name;
	}
	virtual void add(Component *) = 0;
	virtual void remove(Component *) = 0;
	virtual void display(int) = 0;
};

class Leaf :public Component
{
public:
	Leaf(string name) :Component(name)
	{}
	void add(Component *c)
	{
		cout << "leaf cannot add" << endl;
	}
	void remove(Component *c)
	{
		cout << "leaf cannot remove" << endl;
	}
	void display(int depth)
	{
		string str(depth, '-');
		str += name;
		cout << str << endl;
	}
};

class Composite :public Component//Composite :��ϳɵ�
{
private:
	vector<Component*> component;
public:
	Composite(string name) :Component(name)
	{}
	void add(Component *c)
	{
		component.push_back(c);
	}
	void remove(Component *c)
	{
		vector<Component*>::iterator iter = component.begin();
		while (iter != component.end())
		{
			if (*iter == c)
			{
				component.erase(iter);
			}
			iter++;
		}
	}
	void display(int depth)
	{
		string str(depth, '-');
		str += name;
		cout << str << endl;

		vector<Component*>::iterator iter = component.begin();
		while (iter != component.end())
		{
			(*iter)->display(depth + 2);
			iter++;
		}
	}
};


/*С���ı�����һ��leaf,����С����display��leaf��display,ֱ�Ӵ�ӡ С��
Сǿ��Ȼ
С���ı�����һ��Componsite,��һ�������,��ӡС���൱��Ҫ����Conposite�Ĵ�ӡ,��һ���ݹ����*/
int main()
{
	Component *p = new Composite("С��");
	p->add(new Leaf("С��"));
	p->add(new Leaf("Сǿ"));

	Component *sub = new Composite("С��");/*���麯����һ��������Ϊ�������ʽ�������һ����ͬ���͵�����,*/
	sub->add(new Leaf("С��"));
	sub->add(new Leaf("С��"));
	sub->add(new Leaf("С��"));

	p->add(sub);
	p->display(0);

	cout << "*******" << endl;
	sub->display(2);

	cin.get();

	return 0;
}