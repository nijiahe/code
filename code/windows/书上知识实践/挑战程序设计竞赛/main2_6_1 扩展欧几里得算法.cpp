#include "common.h"

//gcd
int gcd(int a, int b) {
	a = a > 0 ? a : -a;
	b = b > 0 ? b : -b;
	int d = 0;
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//extgcd,求ax+by=gcd(a,b)中的a,b的值,并返回gcd(a,b)
int extgcd(int a,int b,int &x,int &y) {
	int d = a;//d会等于a!=0,b=0时的a的值
	if (b == 0) {
		x = 1, y = 0;
	}
	else {
		d = extgcd(b, a%b, x, y);
		//根据数学归纳法,可由下一次递归的结果来得到这次递归的结果
		int temp = y;
		y = x - (a / b)*y;
		x = temp;
	}
	return d;
}

int main2_6_1() {
	int x, y;
	int a = 12, b = 5;
	int d = extgcd(a, b, x, y);
	std::cout << "a is " << a << ",b is " << b;
	std::cout << ",gcd(a,b) is " << d << ", x = " << x << " , y = " << y << std::endl;

	return 0;
}