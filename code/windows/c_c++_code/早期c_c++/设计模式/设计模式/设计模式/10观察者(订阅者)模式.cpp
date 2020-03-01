#include <iostream>
#include <string>
#include <list>
using namespace std;

//观察者模式：观察者模式定义了一种一队多的依赖关系，
//让多个观察者对象同时监听某一个主题对象。
//这个主题对象在状态上发生变化时，会通知所有观察者对象，
//使他们能够自动更新自己。

//监视者的类，管理所有的观察者，增加或者删除，发出消息，让观察者处理
//观察者的类需要接受消息并处理

/*访问者模式通过创建一个观察者,和N个被通知者,观察者里存储被通知者的数组的地址,被通知者里存储观察者的地址,用这样的方式实现信息传递*/
/*设计人员站在管理观察者的角度解决问题,来为观察者添加被通知对象等*/
class Subject; //可以使用subject

class Observer//被通知的对象的抽象
{
protected:
	string name;
	Subject *sub;
public:
	Observer(string name, Subject *sub)//观察者的名字， 监视与通知的类
	{
		this->name = name;//输入名字
		this->sub = sub;//设置谁来通知我
	}
	virtual void update() = 0;//纯虚函数
};

class StockObserver :public Observer //继承，自己实现刷新函数
{//看股票的被通知对象
public:
	StockObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();//此对象接收消息时做的动作
};

class NBAObserver :public Observer
{//看NBA的被通知对象
public:
	NBAObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();//此对象接受不同消息时做的不同动作
};

class Subject  //
{
protected:
	list<Observer*> observers;///存储被通知对象的数组
public:
	string action;//消息内容
	virtual void attach(Observer*) = 0;//添加一个被通知对象
	virtual void detach(Observer*) = 0;//删除一个被通知对象
	virtual void notify() = 0;//实现监听的基类
};


class Secretary :public Subject
{
	void attach(Observer *observer)  //载入通知的列表
	{
		observers.push_back(observer);
	}
	void detach(Observer *observer)//删除
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
	void notify()  ///通知,对数组内的每个被通知者传入消息
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			(*iter)->update();
			++iter;
		}
	}
};

void StockObserver::update()//被通知对象存储着通知人的指针,用来接收通知人的消息
{
	cout << name << " 收到消息：" << sub->action << endl;
	if (sub->action == "梁所长来了!")
	{
		cout << "我马上关闭股票，装做很认真工作的样子！" << endl;
	}
	if (sub->action == "去喝酒！")
	{
		cout << "我马上走" << endl;
	}
}

void NBAObserver::update()
{
	cout << name << " 收到消息：" << sub->action << endl;
	if (sub->action == "梁所长来了!")
	{
		cout << "我马上关闭NBA，装做很认真工作的样子！" << endl;
	}

	if (sub->action == "去喝酒！")
	{
		cout << "我马上拍" << endl;
	}
}

int mainJ()
{
	Subject *dwq = new Secretary();//消息监视，监视(dwq是一个观察者)

	Observer *xs = new NBAObserver("xiaoshuai", dwq);//订阅消息
	Observer *zy = new NBAObserver("zouyue", dwq);//(名字,谁通知)
	Observer *lm = new StockObserver("limin", dwq);

	dwq->attach(xs);//添加三个被通知对象
	dwq->attach(zy);
	dwq->attach(lm);//增加到队列

	dwq->action = "去吃饭了！";
	dwq->notify();
	dwq->action = "去喝酒！";
	dwq->notify();
	cout << endl;
	dwq->action = "梁所长来了!";
	dwq->notify();
	cin.get();
	return 0;
}