#include <iostream>
#include <vector>
#include <string>
using namespace std;
//合成模式：合成模式将对象组织到树结构中，可以用来描述整体与部分的关系。
//合成模式就是一个处理对象的树结构的模式。合成模式把部分与整体的关系用树结构表示出来。
//合成模式使得客户端把一个个单独的成分对象和由他们复合而成的合成对象同等看待。


/*小王的本质是一个leaf,所以小王的display是leaf的display,直接打印 小王
小强毅然
小虎的本质是一个Componsite,是一个混合体,打印小虎相当于要调用Conposite的打印,是一个递归调用*/

/*实现了类的层次感*/
class Component//部件
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

class Composite :public Component//Composite :混合成的
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


/*小王的本质是一个leaf,所以小王的display是leaf的display,直接打印 小王
小强毅然
小虎的本质是一个Componsite,是一个混合体,打印小虎相当于要调用Conposite的打印,是一个递归调用*/
int main()
{
	Component *p = new Composite("小李");
	p->add(new Leaf("小王"));
	p->add(new Leaf("小强"));

	Component *sub = new Composite("小虎");/*用虚函数将一个子类作为父类的形式保存进另一个相同类型的子类,*/
	sub->add(new Leaf("小王"));
	sub->add(new Leaf("小明"));
	sub->add(new Leaf("小柳"));

	p->add(sub);
	p->display(0);

	cout << "*******" << endl;
	sub->display(2);

	cin.get();

	return 0;
}