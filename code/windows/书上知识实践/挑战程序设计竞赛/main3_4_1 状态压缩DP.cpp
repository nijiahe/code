#include "common.h"
#include <stack>

//状态压缩DP:这里指将走过和未走过的状态压缩为位图bitmap
//每个节点必须且只走一次的图最短路径算法:图为挑战程序设计竞赛P191所示

#define MAX_N 15//最大n,此处为 2<<n<<15
#define INF INT_MAX

int dp[1 << MAX_N][MAX_N];//动态规划用的数组,存的是走到此种状态之后走完剩下全程所需要的最短路径

//针对了INF相加不会溢出的加法
inline int add(int a, int b) {
	if (a == INF || b == INF)
		return INF;
	return a + b;
}

//传入初始图,已访问点集合,现在的位置,最终位置,返回此种情况剩余还需要走的最短路径长度(放弃记录路径了)
template<int N>
int go_must_and_only_once(int d[][N], int S, int v,int E) {
	//已经获得过了
	if (dp[S][v] != INF)
		return dp[S][v];
	if (S == (1 << N) - 1 && v == E)//此种状态已经走完了,不需要继续走了
		return dp[S][v]=0;
	int res = INF;
	for (int u = 0; u < N; u++) {
		if (!(S >> u & 1)) {//选择下一个没走过的节点
			int n = add(d[v][u], go_must_and_only_once(d, S | 1 << u, u, E));
			if (res > n)
				res = n;
		}
	}
	return dp[S][v] = res;
}

int main3_4_1() {
	int n = 5;//共5个顶点
	int d[5][5] = {//图
		INF,	3,		INF,	4,		INF,
		INF,	INF,	5,		INF,	INF,
		4,		INF,	INF,	5,		INF,
		INF,	INF,	INF,	INF,	3,
		7,		6,		INF,	INF,	INF
	};
	for (int i = 0; i < 1 << MAX_N; i++)
		for (int j = 0; j < MAX_N; j++)
			dp[i][j] = INF;
		
	int start = 0;

	//从节点0开始,当前走过的集合为0,节尾是0
	int l = go_must_and_only_once<5>(d, 0, start, start);
	cout << "The cost is:" << l << endl;


	return 0;

}