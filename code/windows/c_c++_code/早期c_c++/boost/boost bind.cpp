#include<boost/bind.hpp>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>//函数包装器

using namespace std;
using namespace boost;
//继承二进制函数类的一些函数
class add1:public binary_function<int,int,void>//参数1,参数2，返回值
{
public:
	void operator()(int i,int j) const
	{
		cout << i + j << endl;
	}

};
/*①*/
/*使用c++自带的bind*/
/*将值10加至容器V的每个元素之上,并使用标准输出流显示结果
add()函数转换为一个派生于std::binary_function的函数对象*/
void mainB()
{
	vector<int> myvec;
	myvec.push_back(11);
	myvec.push_back(22);
	myvec.push_back(33);
	//bind1st将函数绑定一个默认参数
	for_each(myvec.begin(), myvec.end(), bind1st(add1(),10));
	cin.get();
}

/*②*/
/*使用boost库中的bind*/
/*不需要为了使用for_each这样的函数而将函数转换为对象,
add()函数需要两个参数,第一个参数为10,第二个参数是for_each传入的值,在bind里用占位符占位*/
void add(int i, int j)
{
	cout << i<<" " << j << " " << endl;
	cout << i + j << endl;
}

void mainC()
{
	vector<int> myvec;
	myvec.push_back(11);
	myvec.push_back(22);
	myvec.push_back(33);
	//bind(函数地址,默认值,占一个默认位)
	for_each(myvec.begin(), myvec.end(),bind(add, 10,_1));
	cin.get();
}