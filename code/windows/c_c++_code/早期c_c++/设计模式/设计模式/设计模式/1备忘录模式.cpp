#include<iostream>
#include<string>
#include<vector>

/*����¼ģʽ:��һ���ౣ�浱ǰ״̬,
��һ����ʵ�ֶ�״̬�Ĳ���,
��һ���ֿⱣ����ֹ�������״̬*/


using namespace std;

class Memo//�������������״̬
{
public:
	string state;
	Memo(string state) :state(state)
	{

	}
};
class Originator//������ഴ�������Ǹ���,����״̬
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

class Caretaker//�ֿ�
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

	Memo* memo1 = new Memo("on");//���浱ǰ״̬
	og->setMemo(memo1);//����״̬
	og->show();//�ص����״̬
	ct->save(og->state);//�������״̬���ֿ�

	/*����ڶ���״̬*/
	Memo* memo2 = new Memo("off");
	og->setMemo(memo2);
	og->show();
	ct->save(og->state);

	/*���Ҫ�ص���һ��״̬,���òֿ��ڵ�����*/
	og->setMemo(ct->getstate(0));
	og->show();

	cin.get();
}