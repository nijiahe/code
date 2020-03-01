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

int main11_2_2()
{
	std::allocator<std::string> alloc;//����һ�����Է���string��allocator����
	std::string* p = alloc.allocate(5);//����5��ԭʼ��,δ������ڴ�,���Կ�����Ƭ�ڴ�Ĵ�СΪ5��string���õ�,��δ��ʼ����,pָ��ͷ��ָ��
	std::string* q = p; 
	for (int i = 0; i < 5; i++,q++)
		alloc.construct(q, std::string("Num" + std::to_string(i)));
	for (int i = 0; i < 5; i++)
		std::cout << *(p + i) << std::ends;
	std::cout << std::endl;
	//��Ҫɾ��allocator���������ڴ�,���ȶ����ϵĶ����������,��������ռ�еĶ�̬�ڴ��ͷ�
	q = p;
	for (int i = 0; i < 5; i++, q++)
		alloc.destroy(q);
	alloc.deallocate(p, 5);
	//����,allocator�ṩ�˿��������δ��ʼ���ڴ���㷨,������ԭʼ�ڴ�һ���Գ�ʼ��������
	/*
	std::uninitialized_copy(begin,end,begin2);//��begin-end֮���Ԫ�ؿ�����begin2��ʼ��ԭʼ�ڴ���,begin2��ʼ��ԭʼ�ڴ���Ҫ�㹻��
	std::uninitialized_copy_n(begin,number,begin2);//����������ͬ,����end��number����������,����ָʾ����������
	std::uninitialized_fill(begin,end,t);//������,��begin-end֮���ԭʼ�ڴ������t
	std::uninitialized_fill(begin,number,t);//������ͬ,����end������number��ȡ��
	*/

	
	system("pause");
	return 0;
}
