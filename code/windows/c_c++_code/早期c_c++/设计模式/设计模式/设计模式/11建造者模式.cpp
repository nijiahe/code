#include <string>
#include <iostream>
#include <vector>
using namespace std;
//建造模式：将产品的内部表象和产品的生成过程分割开来，
//从而使一个建造过程生成具有不同的内部表象的产品对象。
//建造模式使得产品内部表象可以独立的变化，
//客户不必知道产品内部组成的细节。
//建造模式可以强制实行一种分步骤进行的建造过程。
//

class Person  //抽象类，预留ule接口
{
public:
	virtual void createHead() = 0;
	virtual void createHand() = 0;
	virtual void createBody() = 0;
	virtual void createFoot() = 0;
};

class ThinPerson :public Person  ///实现抽象类瘦子，
{
	void createHead()
	{
		cout << "thin head" << endl;
	}
	void createHand()
	{
		cout << "thin hand" << endl;
	}
	void createBody()
	{
		cout << "thin body" << endl;
	}
	void createFoot()
	{
		cout << "thin foot" << endl;
	}
};

class FatPerson :public Person //胖子
{
	void createHead()
	{
		cout << "fat head" << endl;
	}
	void createHand()
	{
		cout << "fat hand" << endl;
	}
	void createBody()
	{
		cout << "fat body" << endl;
	}
	void createFoot()
	{
		cout << "fat foot" << endl;
	}
};


class Director
{
private:
	Person *p;//基类的指针
public:
	Director(Person *temp) //传递对象
	{
		p = temp;//虚函数实现多态
	}
	void create()
	{
		p->createHead();
		p->createHand();
		p->createBody();
		p->createFoot();
	}
};

//客户端代码：
int mainK()
{
	Person *p = new FatPerson();
	Director *d = new Director(p);
	d->create();
	delete d;
	delete p;



	cin.get();
	return 0;
}