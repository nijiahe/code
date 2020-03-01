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
#include <type_traits>

/*
有一种需求为,模板类型为T,返回值为*T,则正常应该如下两种定义:
template<typename It>	decltype(*T) fcn(It beg, It end){return *beg;}
template<typename It>	decltype(*beg) fcn(It beg, It end){return *beg;}
但这都是不可行的,第一种一看就是不可行的,对一个类型解引用一看就是错的,第二种也是不行的,因为此时还未定义beg
所以,尾后返回类型可以解决这一问题,因为此时返回类型被写在后面,而那时编译器已经知道了beg是何类型
如下:(注意:尾后返回类型的返回值需要auto，类型说明符)
由于解引用操作*返回左值,所以返回的类型为 T &
若想只返回T类型,此时可以用标准库定义在头文件type_traits中的类型转换模板
例如remove_reference<decltype(*beg)>::type就是int类型T,而不是T &1
*/

template<typename It>	
auto fcn(It beg, It end) ->decltype(*beg){ 
	/*...*/
	return *beg; 
}

//练习题:返回值足够大的add版本,即会根据返回加法的结果自动选用合适的类型
template<typename T>
auto add(T lhs,T rhs)->decltype(lhs + rhs)
{
	return lhs + rhs;
}

int main16_2_3()
{
	

	system("pause");
	return 0;
}