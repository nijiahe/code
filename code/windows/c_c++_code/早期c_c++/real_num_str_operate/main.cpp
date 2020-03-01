#include"bigdata_calculate.h"
#include<iostream>
#include<stdlib.h>

int main()
{
	cal a;
	a.init_cal("9999999999999999999.999999999999", "888888888888888888888888.8888888888");
	std::cout << a.add() << std::endl;
	system("pause");
	return 0;
}
