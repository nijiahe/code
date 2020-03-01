#include <iostream>
#include <string>
using namespace std;
//适配器（变压器）模式：把一个类的接口变换成客户端所期待的另一种接口
//，从而使原本因接口原因不匹配而无法一起工作的两个类能够一起工作。
//适配类可以根据参数返还一个合适的实例给客户端。

/*原理:将两个类通过继承或者包含指针的方式用一个类封装,类的接口保留想要的,实现在类中用这个接口调用另外的功能*/

class Player
{
public:
	string name;
	Player(string name)
	{
		this->name = name;
	}
	virtual void attack() = 0;
	virtual void defence() = 0;
};

class Forwards :public Player
{
public:
	Forwards(string name) :Player(name) {}
	void attack()
	{
		cout << name << " 前锋进攻" << endl;
	}
	void defence()
	{
		cout << name << " 前锋防守" << endl;
	}
};

class Center :public Player
{
public:
	Center(string name) :Player(name) {}
	void attack()
	{
		cout << name << " 中锋进攻" << endl;
	}
	void defence()
	{
		cout << name << " 中锋防守" << endl;
	}
};

class Backwards :public Player
{
public:
	Backwards(string name) :Player(name) {}
	void attack()
	{
		cout << name << " 后卫进攻" << endl;
	}
	void defence()
	{
		cout << name << " 后卫防守" << endl;
	}
};
/*****************************************************************/
class ForeignCenter
{
public:
	string name;
	ForeignCenter(string name)
	{
		this->name = name;
	}
	void myAttack()
	{
		cout << name << " 外籍中锋进攻" << endl;
	}
	void myDefence()
	{
		cout << name << " 外籍后卫防守" << endl;
	}
};
/*****************************************************************/
class Translator :public Player
{
private:
	ForeignCenter *fc;
public:
	Translator(string name) :Player(name)
	{
		fc = new ForeignCenter(name);
	}
	void attack()
	{
		fc->myAttack();
	}
	void defence()
	{
		fc->myDefence();
	}
};
/*****************************************************************/
int mainP()
{
	Player *p1 = new Center("李俊宏");
	p1->attack();
	p1->defence();

	Translator *tl = new Translator("姚明");
	tl->attack();
	tl->defence();
	cin.get();
	return 0;
}