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

//extgcd,��ax+by=gcd(a,b)�е�a,b��ֵ,������gcd(a,b)
int extgcd(int a,int b,int &x,int &y) {
	int d = a;//d�����a!=0,b=0ʱ��a��ֵ
	if (b == 0) {
		x = 1, y = 0;
	}
	else {
		d = extgcd(b, a%b, x, y);
		//������ѧ���ɷ�,������һ�εݹ�Ľ�����õ���εݹ�Ľ��
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