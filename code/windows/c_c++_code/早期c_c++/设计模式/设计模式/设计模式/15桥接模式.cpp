#include <iostream>
#include <string>
using namespace std;
//����ģʽ����������ʵ�ֻ����ʹ�ö��߿��Զ����ı仯��

//Ҳ����˵������֮���ǿ���������������

//Ҳ����ָ��һ�����ϵͳ�ĳ��󻯺�ʵ�ֻ�֮��ʹ����� 

/// �ۺϹ�ϵ�����Ǽ̳й�ϵ���Ӷ�ʹ���߿��Զ����ı仯��


//�����ܳ���,�����ù��ܵĽӿ�Ҳ����,��������ʵ��һ���ӿڵ��úܶ๦��
class HandsetSoft
{
public:
	virtual void run() = 0;
};

class HandsetGame :public HandsetSoft
{
public:
	void run()
	{
		cout << "�����ֻ���Ϸ" << endl;
	}
};

class HandsetAddressList :public HandsetSoft
{
public:
	void run()
	{
		cout << "�����ֻ�ͨѶ¼" << endl;
	}
};
/*�������Ӳ��*/
class HandsetBrand
{
protected:
	HandsetSoft *soft;
public:
	void setHandsetSoft(HandsetSoft *soft)
	{
		this->soft = soft;
	}
	virtual void run() = 0;
};

class HandsetBrandN :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};

class HandsetBrandM :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};

int mainO()
{
	HandsetBrand *hb;
	hb = new HandsetBrandM();

	hb->setHandsetSoft(new HandsetGame());
	hb->run();
	hb->setHandsetSoft(new HandsetAddressList());
	hb->run();

	cin.get();
	return 0;
}