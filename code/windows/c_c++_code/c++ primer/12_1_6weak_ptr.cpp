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

class StrBlobPtr;

class StrBlob
{
	friend class StrBlobPtr;
	friend bool operator==(StrBlob &, StrBlob&);
	friend bool operator!=(StrBlob &, StrBlob&);
public:
	using size_type = std::vector<std::string>::size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string>);
	size_type size() const { return data->size(); };
	bool empty()const { return data->empty(); };
	void push_back(const std::string &t) { data->push_back(t); };
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
	StrBlobPtr begin();//难道这是传说中的迭代器?
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string> > data;
	//如果data[i]不合法,就抛出一个异常
	void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string> >()) {}
StrBlob::StrBlob(std::initializer_list<std::string> l1) : data(std::make_shared<std::vector<std::string> >(l1)) {}
void StrBlob::check(size_type i, const std::string &msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}
void StrBlob::pop_back()
{
	check(0, "pop back() on empty StrBlob");
	data->pop_back();
}
std::string& StrBlob::front()
{
	check(0, "front() on empty StrBlob");
	return data->front();
}
std::string& StrBlob::back()
{
	check(0, "back() back on empty StrBlob");
	return data->back();
}
const std::string& StrBlob::front() const
{
	check(0, "front() on empty StrBlob");
	return data->front();
}
const std::string& StrBlob::back() const
{
	check(0, "back() back on empty StrBlob");
	return data->back();
}

bool operator==(StrBlob &sb1, StrBlob &sb2)
{
	return sb1.data == sb2.data;
}

bool operator!=(StrBlob &sb1, StrBlob &sb2)
{
	return sb1.data != sb2.data;
}

class StrBlobPtr {
public:
	StrBlobPtr() :curr(0) {};
	StrBlobPtr(StrBlob &a,size_t sz =0):wptr(a.data),curr(sz){}
	std::string& operator*() const { 
		auto p = check(curr, "dereference past end");//p是指向vector的shared_ptr
		return (*p)[curr];//返回vector中的string
	}
	//重载->实质:->的返回值委托给*的返回,并取其地址,这样就实现了*和->之间的意义一致,即*指向实体,->指向实体的指针
	std::string* operator->()const {
		return &this->operator*();
	}
	std::string& deref()const;
	StrBlobPtr& incr();//前缀递增
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
private:
	//若检查成功,check返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<std::string> > check(std::size_t, const std::string &)const;
	//保存的是weak_ptr,不添加引用计数,其所指对象可能已被销毁
	std::weak_ptr<std::vector<std::string> > wptr;
	std::size_t curr;//数组中的当前位置
};

std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(std::size_t i, const std::string &msg)const
{
	std::shared_ptr<std::vector<std::string> > ret = wptr.lock();
	if (!ret)//未绑定,返回空ptr
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())//注:i是下标
		throw std::out_of_range(msg);
	return ret;//若不抛出异常,返回ret
}

std::string& StrBlobPtr::deref()const
{
	std::shared_ptr<std::vector<std::string> > p = this->check(curr, "derefence past end");
	return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

int main12_1_6()
{
	/*
	weak_ptr名为弱指针,由shared_ptr初始化,指向shared_ptr指向的对象,但又不会增加shared_ptr的引用计数
	可以调用w.use_count返回当前对象被shared_ptr的引用数量
	可以调用w.lock()通过条件判断引用数量来判断对象还是否存在,从而返回一个有用的shared_ptr指针或者是一个空shared_ptr
	*/

//练习题:
	std::ifstream file("F:\\word translation2.txt");
	std::string word;
	StrBlob strb;
	while (file >> word)
		strb.push_back(word);
	StrBlobPtr begin = strb.begin();
	for (StrBlobPtr begin = strb.begin(); begin != strb.end(); begin.incr())
		std::cout << begin.deref() << std::ends;
	std::cout << std::endl;



	system("pause");
	return 0;
}
