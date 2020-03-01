#include<iostream>
#include<array>
#include<vector>
using namespace std;
template<typename T>
class group01
{
private:
	T* ptr;
	int len;
public:
	group01()
	{
		ptr = NULL;
		len = 0;
	}
	~group01()
	{
		delete[] ptr;
		ptr = NULL;
	}
	void add(T n)
	{
		T* oldptr = ptr;
		ptr = new T[len + 1];
		if (ptr != NULL)
		{
			for (int i = 0; i < len; i++)
			{
				ptr[i] = oldptr[i];
			}
			delete[] oldptr;
			oldptr = NULL;
		}
		ptr[len] = n;
		len++;
	}
	T& operator[](int index)
	{
		if (index<0 || index>len - 1)
		{
			cout << "bad operate" << endl;
		}
		else { return ptr[index]; }
	}
};

void main01()
{
	group01<int>group1;
	group1.add(3);
	cout << group1[0] << endl;
	std::cin.get();
}
template<typename T,int n>
class groups
{
	T* data;
	int len;
public:
	groups()
	{
		data = new T[n];
		len = n;
	}
	~groups()
	{
		delete[]data;
		data = NULL;
	}
	T& operator[](int index)
	{
		return data[n];
	}
};
void main()
{
	groups<int, 3>mygroups;
	mygroups[0]=0;
	std::cout << mygroups[0] << std::endl;
	std::cin.get();
}








/*#include<iostream>
#include <string>
using namespace std;

template< class T>
class MyArray
{
public:
	T *data;
	int len;

public:
	MyArray()
	{
		data = NULL;
		len = 0;
	}

	~MyArray()
	{
		delete[] data;
	}

	T& operator [](int index);

	void push(T d);

};

template <class T>
T& MyArray<T>::operator [] (int index)
{
	if (index<0 || index>(len - 1))
	{
		cout << "Bad subscript!" << endl;
		exit(1);

	}
	return data[index];

}

template <class T>
void MyArray<T>::push(T d)
{
	T *pdata = data;
	data = new T[len + 1];
	if (pdata != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			data[i] = pdata[i];
		}
		delete[] pdata;
		pdata = NULL;
	}
	data[len] = d;
	len++;
}

struct student
{
	string name;
	int    age;
};
int main(int argc, char* argv[])

{
	MyArray<int> a;  //整形测试；
	a.push(11);
	a.push(22);
	a.push(33);
	a.push(55);
	a[0] = 44;

	for (int i = 0; i<4; i++)
		cout << a[i] << endl;

	MyArray<struct student> stu;   //自定义类型测试；
	for (int i = 0; i<2; i++)
	{
		struct student  stu1;
		cout << " input the student's infor : " << endl;
		cin >> stu1.name >> stu1.age;
		stu.push(stu1);
	}

	for (int i = 0; i<2; i++)
		cout << stu[i].name << " " << stu[i].age << endl;
	return 0;
}
*/