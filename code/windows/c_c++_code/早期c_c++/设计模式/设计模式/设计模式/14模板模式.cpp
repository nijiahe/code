#include<iostream>
#include <vector>
#include <string>
using namespace std;
/*模板方法模式：模板方法模式准备一个抽象类，
将部分逻辑以具体方法以及具体构造子的形式实现，
然后声明一些抽象方法来迫使子类实现剩余的逻辑。
不同的子类可以以不同的方式实现这些抽象方法，
从而对剩余的逻辑有不同的实现。先制定一个顶级逻辑框架，
而将逻辑的细节留给具体的子类去实现。*/

/*将一个做好大部分框架的类抽象,然后添加几个抽象方法,用于构造不同的子类,可以实现贴标签式生产*/
/*可以实现本地化,即在不同的地区添加不同的语言方法*/
class AbstractClass
{
public:
	void Show()
	{
		cout << "我是" << GetName() << endl;
	}
protected:
	virtual string GetName() = 0;
};

class Naruto : public AbstractClass
{
protected:
	virtual string GetName()
	{
		return "火影史上最帅的六代目---一鸣惊人naruto";
	}
};

class OnePice : public AbstractClass
{
protected:
	virtual string GetName()
	{
		return "我是无恶不做的大海贼---路飞";
	}
};

//客户端
int mainN()
{
	Naruto* man = new Naruto();
	man->Show();

	OnePice* man2 = new OnePice();
	man2->Show();

	cin.get();
	return 0;
}
