#include<iostream>
#include<set>
#include<string>

using namespace std;

struct strless
{
	bool operator()(const char *str1,const char* str2) const
	{/*若str1<str2返回负值,若str1=str2返回0,若str1>str2返回正数,比较大小和字典排序方法一样*/
		return strcmp(str1, str2)<0 ;
	}
};


void main60()
{/*元素类型,排序方法*/
	set<char*, strless>myset1;
	myset1.insert("zzt");
	myset1.insert("ly");
	myset1.insert("njh");
	for (auto ibegin = myset1.begin(); ibegin != myset1.end(); ibegin++)
	{
		cout << *ibegin << endl;
	}
	cin.get();
}

void main61()
{
	const char* cmd[] = { "abc","calc","ly","njh","zzt" };
	set<const char*, strless>myset1(cmd, cmd + 5, strless());
	for (auto ibegin = myset1.begin(); ibegin != myset1.end(); ibegin++)
	{
		cout << *ibegin << endl;
	}
	/*当用字符串insert的时候返回一个pair类型,可以用自己创建的pair模板类型实例化接收*/
	//pair<set<const char*>::iterator, bool>p=myset1.insert("9876");
	auto p = myset1.insert("9876");
	/*p.first返回一个conditional类型,重载了*,*p输出insert的值,p.second返回的是bool值*/
	cout << *(p.first) << " " << p.second << endl;
	/*set<const char *, strless>::iterator pfind = myset1.find("abc");
	cout << "\n\n\n" << *pfind << endl;*/
	cin.get();
} 