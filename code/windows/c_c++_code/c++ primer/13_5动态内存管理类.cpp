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
#include <cstring>

class StrVec 
{
public:
	StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
	StrVec(std::initializer_list<std::string> strs) :elements(nullptr),first_free(nullptr),cap(nullptr){
		auto data = alloc_n_copy(strs.begin(), strs.end());
		elements = data.first;
		cap = first_free = data.second;
	}
	StrVec(const StrVec&);
	StrVec &operator=(const StrVec&);
	~StrVec();
	void push_back(const std::string&);
	size_t size() const { return first_free - elements; }//返回元素数量
	size_t capacity() const { return cap - elements; }//返回实际向堆申请了的容量
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

private:
	std::allocator<std::string> alloc;//分配器,用以分配元素
	void chk_n_alloc() { if (size() == capacity())reallocate(); }//动态分配函数,保证有一个以上的新元素空间,否则realloc
	//分配内存,并拷贝一个给定范围中的元素,返回被分配
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();//销毁元素并释放内存
	void reallocate();//重新分配一块更大的内存,并且拷贝已有元素
	std::string *elements;//指向数组首元素的指针
	std::string *first_free;//指向数组第一个空闲元素的指针,用以新建元素时放置在这个位置
	std::string *cap;//指向数组尾后位置的指针,即实际分配的空间的末尾
};

void StrVec::push_back(const std::string& s)
{
	chk_n_alloc();//首先检查并分配空间
	alloc.construct(first_free++, s);//在当前最开始的空闲处创建对象,并且first_free++
}

std::pair<std::string*,std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
	auto data = alloc.allocate(e - b);//分配参数表示的迭代范围的大小的内存,返回其指针
	//uninitialized_copy将参数表示范围内存拷贝到被分配的data上,其返回尾后指针,所以此函数返回被分配的内存的头指针和尾指针组成的pair
	return { data,std::uninitialized_copy(b,e,data) };
	return std::pair<std::string*, std::string*>();
}

void StrVec::free()
{
	if (elements) {
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;//分配两倍于当前大小的空间
	auto newdata = alloc.allocate(newcapacity);
	//开始复制转移源地址空间中的数据到新地址空间
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));//std::move返回右值,所以这里的意义就是利用std::move返回的右值进行构造,这样就避免了构造和释放string
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

int main13_5()
{

	system("pause");
	return 0;
}
