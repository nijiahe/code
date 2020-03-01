#include<iostream>
#include<string>
#include<vector>

/*备忘录模式:用一个类保存当前状态,
用一个类实现对状态的操作,
用一个仓库保存出现过的所有状态*/


using namespace std;

class Memo//这个类用来保存状态
{
public:
	string state;
	Memo(string state) :state(state)
	{

	}
};
class Originator//用这个类创造上面那个类,创造状态
{
public:
	Memo* state;
	void setmemo(Memo* memo)
	{
		state = memo;
	}
	Originator()
	{

	}
	void setMemo(Memo* state)
	{
		this->state = state;
	}
	void show()
	{
		cout << state->state << endl;
	}
};

class Caretaker//仓库
{
public:
	vector<Memo*>memo;
	void save(Memo* memo)
	{
		(this->memo).push_back(memo);
	}
	Memo* getstate(int i)
	{
		return memo[i];
	}
};

void mainA()
{
	Originator* og = new Originator();
	Caretaker* ct = new Caretaker;

	Memo* memo1 = new Memo("on");//保存当前状态
	og->setMemo(memo1);//保存状态
	og->show();//回到这个状态
	ct->save(og->state);//保存这个状态到仓库

	/*保存第二个状态*/
	Memo* memo2 = new Memo("off");
	og->setMemo(memo2);
	og->show();
	ct->save(og->state);

	/*如果要回到第一个状态,调用仓库内的数据*/
	og->setMemo(ct->getstate(0));
	og->show();

	cin.get();
}