#pragma once

#include "common.h"

//this should be the exponential times of 2
#define _EXP_ACCURACY_ 8192

#define _ERF_PI 3.141592653589793

#define _ERF_N 10000

#define _LN2 0.69314718

namespace MyMath {

	inline long Factorial(long x);                           // 阶乘
	inline double Pow(double x, double y = 2);               // 求x^y
	inline double Square(double x);                          // 求平方
	inline double Cube(double x);                            // 求立方
	inline int Int(double x);                                  // 取整, 不进行四舍五入
	inline double Fabs(double x);                            // 求绝对值
	inline double Arctanh(double x);                           // 求achtanh()
	inline double Ln(double x);                                // 求自然对数
	inline double Exp(double x);                             // 求e的x次幂
	inline double Gen(double x, double y);                     // 求根

	inline double Sqrt(double a);

	//x^n
	template<class _Ty> inline _Ty Pow_Int(_Ty _X, int _Y);

	//error function，here I will use Riemann_Sum to calculate it
	//erf(x) = the cumulation of{ 2 / sqrt(pi)*exp(-z * z) } from 0 to x;
	//2/sqrt(pi) * { ∑[(-1)^n / n! * x^(2n+1)/(2n+1)] + x }
	inline double Erf(double x);

	
}
double strToDouble(const char *str);
int strToInt(const char *str);

namespace MyMath {

	// 计算阶乘
	inline long Factorial(long x) {
		if (0 == x || 1 == x) {
			return 1;
		}
		long ans = 1;
		for (int i = 2; i <= x; i++) {
			ans *= i;
		}
		return ans;
	}

	// 计算求幂, 默认是平方
	// x^y=e^(ln(x)*y)
	double Pow(double x, double y) {
		double d = (Ln(x)*y);
		return Exp(d);
	}

	// 求根
	inline double Gen(double x, double y) {
		return Pow(x, 1 / y);
	}

	inline double Sqrt(double x) {
		return Pow(x, (double)1 / 2);
	}

	// 计算绝对值
	inline double Fabs(double x) {
		if (x < -1e-9)
			return -x;
		return x;
	}

	inline int Int(double x) {
		return static_cast<int>(Fabs(x));
	}

	// 计算 x^2
	inline double Square(double x) {
		return (x*x);
	}

	// 计算 x^3
	inline double Cube(double x) {
		return (x*x*x);
	}

	// arctanh(x)= x + x^3/3 + x^5/5 + ...       (x≤1)
	// 求sinh(y) 会用到
	// 精度为7位
	/*inline double Arctanh(double x) {
		int n = 1;
		double sum = 0, term = x, numer = x, denom = 1;
		while (Fabs(term) > 1e-8)
		{
			sum += term;                            // 求和
			numer = numer * x * x;                  // 分子
			denom = n + 2;                            // 分母
			term = numer / denom;                     // 精度
			n += 2;                                 // 计数
		}
		return sum;
	}*/

	// ln(x) = 2 arctanh((x-1)/(x+1))
	// 调用了Arctanh(double) 方法
	inline double Ln(double x) {
		double ret;
		if (x < 0.01) {
			int times = 0;
			while (x < 1) {
				x *= 2; times++;
			}
			ret = Ln(x) - times * _LN2;
		}
		else if (x > 50) {
			int times = 0;
			while (x > 1) {
				x /= 2; times++;
			}
			ret = Ln(x) + times * _LN2;
		}
		else {
			ret = x;
			while (Fabs(Exp(ret) - x) >= 1e-8) {
				ret = ret + (x / Exp(ret)) - 1;
			}
		}
		return ret;
	}

	// 求e^x 用于Pow( double, double )调用
	// e^x = 1+x+(x^2)/2!+(x^3)/3!+...
	// 精度为7位
	inline  double Exp(double x) {
		bool neg = false;
		if (x < 0) {
			x = Fabs(x); neg = true;
		}
		double ret = 1, term = x, n = 1;
		while (Fabs(term) > 1e-8){
			ret += term;
			++n;
			term = term * x / n;
		}
		neg ? (ret = 1 / ret) : 1;
		return ret;
	}

	template<class _Ty> inline
		_Ty Pow_Int(_Ty _X, int _Y)
	{
		unsigned int _N;
		if (_Y >= 0)
			_N = _Y;
		else
			_N = -_Y;
		for (_Ty _Z = _Ty(1); ; _X *= _X)
		{
			if ((_N & 1) != 0)
				_Z *= _X;
			if ((_N >>= 1) == 0)
				return (_Y < 0 ? _Ty(1) / _Z : _Z);
		}
	}

	//泰勒展开,// 2/sqrt(pi) * { ∑[(-1)^n / n! * x^(2n+1)/(2n+1)] + x }
	double Erf(double x) {//误差函数计算
		if (x <= 0)
			return 0;
		else if (x >= 3.5)
			return 1;
		else {
			double ret = x;
			double x_prev = x;
			for (int n = 1; n < 10000; n++) {
				x_prev = x_prev * (-1)*(2 * n - 1) / n / (2 * n + 1)*x*x;
				ret += x_prev;
			}
			return 2 * ret / Sqrt(_ERF_PI);
		}
		
	}

	template<typename T>T Max(T a, T b) {
		return a > b ? a : b;
	}

	template<typename T>T Min(T a, T b) {
		return a < b ? a : b;
	}
}

