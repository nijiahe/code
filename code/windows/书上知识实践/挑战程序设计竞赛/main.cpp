#define call_main(x)	main##x()

#include <time.h>
#include <stdlib.h>

int main2_6_1();//扩展欧几里得算法 (计算ax+by=gcd(a,b),求x,y)
int main3_1_4();//最大平均值问题,二分查找法
int main3_4_1();//状态压缩DP,每个节点都只能走一次的最短路径图算法

int main() {
	srand(time(NULL));
	call_main(3_4_1);

	return 0;
}