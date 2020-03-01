#include<iostream>

using namespace std;

/*��Ӧ��������û�����Ϣ,��ǰδ����*/


/*��  ����\�û�\��������  ����,���ݲ�ͬ�Ĺ������ò�ͬ���û��Ͳ�ͬ�Ĳ���*/
/*��ͬ���û��в�ͬ������,�ڲ�ͬ�Ĺ����ﱻ���*/
class IUser//���û���һ������
{
public:
	virtual void getUser() = 0;
	virtual void setUser() = 0;
};

class SqlUser :public IUser//Sql�û�
{
public:
	void getUser()//��Sql�з�������û�����Ϣ
	{

	}
	void setUser()//��Sql�д�������û�
	{

	}
};

class AccessUser :public IUser//Access�û�
{
public:
	void getUser()//��Access�ﷵ������û�����Ϣ
	{

	}
	void setUser()//��Access�д�������û�
	{

	}
};

class IDepartment//���ṩ�Ĳ�����һ������
{
public:
	virtual void getDepartment() = 0;
	virtual void setDepartment() = 0;
};

class SqlDepartment:public IDepartment//SQL �ṩ�Ĳ���
{
public:
	void getDepartment()//��SQL�з����ṩ�Ĳ�������Ϣ
	{

	}
	void setDepartment()//��Sql����������������
	{

	}
};

class AccessDepartment :public IDepartment//Access �ṩ�Ĳ���
{
public:
	void getDepartment()//��Access�з����ṩ�Ĳ�������Ϣ
	{

	}
	void setDepartment()//��Access����Ӳ���
	{

	}
};

class IFactory//һ�������ĳ���
{
public:
	virtual IUser* createUser() = 0;
	virtual IDepartment* createDepartment() = 0;
};

class SqlFactory :public IFactory//SQL ����
{
public:
	IUser* createUser()//��SQL�����д���һ��SQL�û�
	{
		return new SqlUser();
	}
	IDepartment* createDepartment()//��SQL�����д���SQL�ṩ�Ĳ���
	{
		return new SqlDepartment;
	}
};

class AccessFactory :public IFactory // Access����
{
public:
	IUser *createUser()//��Access�����д���һ��Access�û�
	{
		return new AccessUser();
	}
	IDepartment *createDepartment()//��Access�����д���һ��Access������
	{
		return new AccessDepartment();
	}
};
/*��Ϊ�û�������н��̵ĽǶ�*/
class DataAccess//ѡ��һ�ֹ���
{
private:
	static string db;
	//string db="access";
public:
	static IUser *createUser()//�����û�
	{
		if (db == "access")
		{
			return new AccessUser();
		}
		else if (db == "sql")
		{
			return new SqlUser();
		}
		return nullptr;
	}
	static IDepartment *createDepartment()//������Ӧ�����Ĳ�������
	{
		if (db == "access")
		{
			return new AccessDepartment();
		}
		else if (db == "sql")
		{
			return new SqlDepartment();
		}
		return nullptr;
	}
};
string DataAccess::db = "sql";

void mainC()
{
	IFactory *factory;//���󹤳�
	IUser *user;//����������
	IDepartment *department;//�ṩ�Ĳ���

	factory = new AccessFactory();//��������ΪAccess����
	user = factory->createUser();//�û�����ΪAccess����������
	department = factory->createDepartment();//������������ΪAccess�������ṩ�Ĳ�������

	user->getUser();//��������û�����Ϣ
	user->setUser();//��������û�

	department->getDepartment();
	department->setDepartment();//�ӿ�

	/*ֱ��ͨ���鹤������*/
	user = DataAccess::createUser();
	department = DataAccess::createDepartment();

	user->getUser();
	user->setUser();
	department->getDepartment();
	department->setDepartment();


	cin.get();


	return;
}