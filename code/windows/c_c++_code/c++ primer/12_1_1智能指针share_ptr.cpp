#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>


//注:函数体后面的const表示出了mutable成员变量以外,其他成员变量不能在此函数中修改
class StrBlob2
{
	friend class StrBlobPtr;
public:
	using size_type = std::vector<std::string>::size_type ;
	StrBlob2();
	StrBlob2(std::initializer_list<std::string>);
	size_type size() const { return data->size(); };
	bool empty()const { return data->empty(); };
	void push_back(const std::string &t) { data->push_back(t); };
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front () const;
	const std::string& back () const;

private:
	std::shared_ptr<std::vector<std::string> > data;
	//如果data[i]不合法,就抛出一个异常
	void check(size_type i, const std::string &msg) const;
};

StrBlob2::StrBlob2():data(std::make_shared<std::vector<std::string> >()){}
StrBlob2::StrBlob2(std::initializer_list<std::string> l1):data(std::make_shared<std::vector<std::string> >(l1)){}
void StrBlob2::check(size_type i, const std::string &msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}
void StrBlob2::pop_back()
{
	check(0, "pop back() on empty StrBlob");
	data->pop_back();
}
std::string& StrBlob2::front()
{
	check(0, "front() on empty StrBlob");
	return data->front();
}
std::string& StrBlob2::back()
{
	check(0, "back() back on empty StrBlob");
	return data->back();
}
const std::string& StrBlob2::front() const
{
	check(0, "front() on empty StrBlob");
	return data->front();
}
const std::string& StrBlob2::back() const
{
	check(0, "back() back on empty StrBlob");
	return data->back();
}

int main12_1_1()
{
	//智能指针和其一些操作保存在memory头文件中
	StrBlob2 strb1{ "11","22","33" };
	strb1.pop_back();


	system("pause");
	return 0;
}
