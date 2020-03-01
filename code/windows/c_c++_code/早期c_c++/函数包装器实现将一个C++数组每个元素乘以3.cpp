#include<iostream>
#include<array>
#include<algorithm>
#include<functional>
#include<vector>
template<typename F>
void run(std::array<int,3> it, F f)
{
	f(it);
}

int main()
{
	using std::array;
	using std::vector;
	array<int, 3 >num= {1, 2, 3};
	std::function<void(array<int, 3>)>fun1 = [](array<int, 3>num)
	{
		array<int, 3>::iterator ibegin, iend;
		ibegin = num.begin();
		iend = num.end();
		for (; ibegin != iend; ibegin++)
		{
			*ibegin = (*ibegin) * 3;
			std::cout << *ibegin << std::endl;
		}
	};
	run(num, fun1);
	


	std::cin.get();
	return 0;
}
