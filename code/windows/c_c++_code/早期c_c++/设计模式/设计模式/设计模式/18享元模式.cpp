#include <iostream>
#include <list>
#include <string>
#include <map>
using namespace std;

//享元模式：FLYWEIGHT在拳击比赛中指最轻量级。
//享元模式以共享的方式高效的支持大量的细粒度对象。
//享元模式能做到共享的关键是区分内蕴状态和外蕴状态。
//内蕴状态存储在享元内部，不会随环境的改变而有所不同。
//外蕴状态是随环境的改变而改变的。外蕴状态不能影响内蕴状态，
//它们是相互独立的。将可以共享的状态和不可以共享的状态从常规类中区分开来，
//将不可以共享的状态从类里剔除出去。客户端不可以直接创建被共享的对象，
//而应当使用一个工厂对象负责创建被共享的对象。
//享元模式大幅度的降低内存中对象的数量。

/*一个接口共享多个功能,并且实现功能不重复创建,优化内存,减少创建的对象数目*/
class WebSite
{
public:
	virtual void use() = 0;//预留接口实现功能
};

class ConcreteWebSite :public WebSite
{
private:
	string name;
public:
	ConcreteWebSite(string name)//实例化
	{
		this->name = name;
	}
	void use()
	{
		cout << "网站分类: " << name << endl;
	}
};

class WebSiteFactory
{
private:
	map<string, WebSite*> wf;
public:
	WebSite *getWebSiteCategory(string key)
	{
		if (wf.find(key) == wf.end())
		{
			wf[key] = new ConcreteWebSite(key);
		}
		return wf[key];
	}
	int getWebSiteCount()
	{
		return wf.size();
	}
};

int mainR()
{
	WebSiteFactory *wf = new WebSiteFactory();

	WebSite *fx = wf->getWebSiteCategory("good");
	fx->use();

	WebSite *fy = wf->getWebSiteCategory("产品展示");
	fy->use();

	WebSite *fz = wf->getWebSiteCategory("产品展示");
	fz->use();


	WebSite *f1 = wf->getWebSiteCategory("博客");
	f1->use();

	WebSite *f2 = wf->getWebSiteCategory("博客");
	f2->use();

	cout << wf->getWebSiteCount() << endl;

	cin.get();
	return 0;
}