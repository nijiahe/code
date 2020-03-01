#include <iostream>
#include <cstdlib>

static int N = 200;

using namespace std;

/*
时间复杂度分析：
当n=0或n=1时为O(1)
当T(0)=T(1)=1;
T(n)=T(n-1)+T(n-2)+1,因为要进行一次加法
根据数学中数列相关知识，设S(n)=(T(n)+1)/2,则S(0)=1,S(1)=1,S(n)=(T(n-1)+T(n-2)+2)/2=S(n-1)+S(n-2),也是一个斐波那契数列，
则T(n)=2S(n)-1为O(指数级）
*//*最普通的递归算法*/
_int64 Fibonacci1(int n) {
	return n < 2 ? n : Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

/*记忆法，记录前两项，用以算下一个，线性递归*/
_int64 Fibonacci2(int n, _int64 &prev) {
	if (n == 0) { prev = 1; return 0; }
	else {
		_int64 prevPrev;
		prev = Fibonacci2(n - 1, prevPrev);
		return prev + prevPrev;
	}
}

/*自下而上，动态规划*/
_int64 Fibonacci3(int n) {
	int i = 0, lef = 0, rig = 1;
	while (i++ < n) {
		rig = lef + rig;
		lef = rig - lef;
	}
	return lef + rig;
}

int main1_452()
{
	_int64 num;
	for (int i = 1; i < N; i++)
		cout << "Fibonacci(" << i << ")" << Fibonacci2(i,num) << endl;


	system("pause");
	return 0;
}