#include<iostream>

using namespace std;

/*还应包含这个用户的信息,当前未包含*/


/*将  工厂\用户\操作方法  抽象,根据不同的工厂设置不同的用户和不同的操作*/
/*不同的用户有不同的需求,在不同的工厂里被完成*/
class IUser//对用户的一个抽象
{
public:
	virtual void getUser() = 0;
	virtual void setUser() = 0;
};

class SqlUser :public IUser//Sql用户
{
public:
	void getUser()//在Sql中返回这个用户的信息
	{

	}
	void setUser()//在Sql中创建这个用户
	{

	}
};

class AccessUser :public IUser//Access用户
{
public:
	void getUser()//在Access里返回这个用户的信息
	{

	}
	void setUser()//在Access中创建这个用户
	{

	}
};

class IDepartment//对提供的操作的一个抽象
{
public:
	virtual void getDepartment() = 0;
	virtual void setDepartment() = 0;
};

class SqlDepartment:public IDepartment//SQL 提供的操作
{
public:
	void getDepartment()//在SQL中返回提供的操作的信息
	{

	}
	void setDepartment()//在Sql中设置添加这个操作
	{

	}
};

class AccessDepartment :public IDepartment//Access 提供的操作
{
public:
	void getDepartment()//在Access中返回提供的操作的信息
	{

	}
	void setDepartment()//在Access中添加操作
	{

	}
};

class IFactory//一个工厂的抽象
{
public:
	virtual IUser* createUser() = 0;
	virtual IDepartment* createDepartment() = 0;
};

class SqlFactory :public IFactory//SQL 工厂
{
public:
	IUser* createUser()//在SQL工厂中创建一个SQL用户
	{
		return new SqlUser();
	}
	IDepartment* createDepartment()//在SQL工厂中创建SQL提供的操作
	{
		return new SqlDepartment;
	}
};

class AccessFactory :public IFactory // Access工厂
{
public:
	IUser *createUser()//在Access工厂中创建一个Access用户
	{
		return new AccessUser();
	}
	IDepartment *createDepartment()//在Access工厂中创建一个Access管理者
	{
		return new AccessDepartment();
	}
};
/*以为用户服务的中介商的角度*/
class DataAccess//选择一种工厂
{
private:
	static string db;
	//string db="access";
public:
	static IUser *createUser()//创建用户
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
	static IDepartment *createDepartment()//返回相应工厂的操作方法
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
	IFactory *factory;//抽象工厂
	IUser *user;//抽象消费者
	IDepartment *department;//提供的操作

	factory = new AccessFactory();//工厂设置为Access工厂
	user = factory->createUser();//用户设置为Access工厂的永固
	department = factory->createDepartment();//操作方法设置为Access工厂的提供的操作方法

	user->getUser();//返回这个用户的信息
	user->setUser();//设置这个用户

	department->getDepartment();
	department->setDepartment();//接口

	/*直接通过虚工厂设置*/
	user = DataAccess::createUser();
	department = DataAccess::createDepartment();

	user->getUser();
	user->setUser();
	department->getDepartment();
	department->setDepartment();


	cin.get();


	return;
}