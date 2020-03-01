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


//ע:����������const��ʾ����mutable��Ա��������,������Ա���������ڴ˺������޸�
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
	//���data[i]���Ϸ�,���׳�һ���쳣
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
	//����ָ�����һЩ����������memoryͷ�ļ���
	StrBlob2 strb1{ "11","22","33" };
	strb1.pop_back();


	system("pause");
	return 0;
}
