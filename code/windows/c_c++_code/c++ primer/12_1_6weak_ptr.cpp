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
	StrBlobPtr begin();//�ѵ����Ǵ�˵�еĵ�����?
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string> > data;
	//���data[i]���Ϸ�,���׳�һ���쳣
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
		auto p = check(curr, "dereference past end");//p��ָ��vector��shared_ptr
		return (*p)[curr];//����vector�е�string
	}
	//����->ʵ��:->�ķ���ֵί�и�*�ķ���,��ȡ���ַ,������ʵ����*��->֮�������һ��,��*ָ��ʵ��,->ָ��ʵ���ָ��
	std::string* operator->()const {
		return &this->operator*();
	}
	std::string& deref()const;
	StrBlobPtr& incr();//ǰ׺����
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
private:
	//�����ɹ�,check����һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<std::string> > check(std::size_t, const std::string &)const;
	//�������weak_ptr,��������ü���,����ָ��������ѱ�����
	std::weak_ptr<std::vector<std::string> > wptr;
	std::size_t curr;//�����еĵ�ǰλ��
};

std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(std::size_t i, const std::string &msg)const
{
	std::shared_ptr<std::vector<std::string> > ret = wptr.lock();
	if (!ret)//δ��,���ؿ�ptr
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())//ע:i���±�
		throw std::out_of_range(msg);
	return ret;//�����׳��쳣,����ret
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
	weak_ptr��Ϊ��ָ��,��shared_ptr��ʼ��,ָ��shared_ptrָ��Ķ���,���ֲ�������shared_ptr�����ü���
	���Ե���w.use_count���ص�ǰ����shared_ptr����������
	���Ե���w.lock()ͨ�������ж������������ж϶����Ƿ����,�Ӷ�����һ�����õ�shared_ptrָ�������һ����shared_ptr
	*/

//��ϰ��:
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
