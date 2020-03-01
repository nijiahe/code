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
	std::allocator<std::string> alloc;//创建一个可以分配string的allocator对象
	std::string* p = alloc.allocate(5);//分配5个原始的,未构造的内存,可以看作这片内存的大小为5个string所用的,且未初始化过,p指向开头的指针
	std::string* q = p; 
	for (int i = 0; i < 5; i++,q++)
		alloc.construct(q, std::string("Num" + std::to_string(i)));
	for (int i = 0; i < 5; i++)
		std::cout << *(p + i) << std::ends;
	std::cout << std::endl;
	//若要删除allocator对象分配的内存,首先对其上的对象进行析构,将对象所占有的动态内存释放
	q = p;
	for (int i = 0; i < 5; i++, q++)
		alloc.destroy(q);
	alloc.deallocate(p, 5);
	//此外,allocator提供了拷贝和填充未初始化内存的算法,用以用原始内存一次性初始化大块对象
	/*
	std::uninitialized_copy(begin,end,begin2);//将begin-end之间的元素拷贝到begin2开始的原始内存中,begin2开始的原始内存需要足够大
	std::uninitialized_copy_n(begin,number,begin2);//与上作用相同,但是end被number参数所代替,用以指示拷贝的数量
	std::uninitialized_fill(begin,end,t);//填充操作,在begin-end之间的原始内存内填充t
	std::uninitialized_fill(begin,number,t);//与上相同,但是end参数被number所取代
	*/

	
	system("pause");
	return 0;
}
