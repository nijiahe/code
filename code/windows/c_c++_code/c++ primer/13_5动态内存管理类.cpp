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
	size_t size() const { return first_free - elements; }//����Ԫ������
	size_t capacity() const { return cap - elements; }//����ʵ����������˵�����
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

private:
	std::allocator<std::string> alloc;//������,���Է���Ԫ��
	void chk_n_alloc() { if (size() == capacity())reallocate(); }//��̬���亯��,��֤��һ�����ϵ���Ԫ�ؿռ�,����realloc
	//�����ڴ�,������һ��������Χ�е�Ԫ��,���ر�����
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();//����Ԫ�ز��ͷ��ڴ�
	void reallocate();//���·���һ�������ڴ�,���ҿ�������Ԫ��
	std::string *elements;//ָ��������Ԫ�ص�ָ��
	std::string *first_free;//ָ�������һ������Ԫ�ص�ָ��,�����½�Ԫ��ʱ���������λ��
	std::string *cap;//ָ������β��λ�õ�ָ��,��ʵ�ʷ���Ŀռ��ĩβ
};

void StrVec::push_back(const std::string& s)
{
	chk_n_alloc();//���ȼ�鲢����ռ�
	alloc.construct(first_free++, s);//�ڵ�ǰ�ʼ�Ŀ��д���������,����first_free++
}

std::pair<std::string*,std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
	auto data = alloc.allocate(e - b);//���������ʾ�ĵ�����Χ�Ĵ�С���ڴ�,������ָ��
	//uninitialized_copy��������ʾ��Χ�ڴ濽�����������data��,�䷵��β��ָ��,���Դ˺������ر�������ڴ��ͷָ���βָ����ɵ�pair
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
	auto newcapacity = size() ? 2 * size() : 1;//���������ڵ�ǰ��С�Ŀռ�
	auto newdata = alloc.allocate(newcapacity);
	//��ʼ����ת��Դ��ַ�ռ��е����ݵ��µ�ַ�ռ�
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));//std::move������ֵ,��������������������std::move���ص���ֵ���й���,�����ͱ����˹�����ͷ�string
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
