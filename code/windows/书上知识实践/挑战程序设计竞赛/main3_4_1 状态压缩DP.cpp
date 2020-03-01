#include "common.h"
#include <stack>

//״̬ѹ��DP:����ָ���߹���δ�߹���״̬ѹ��Ϊλͼbitmap
//ÿ���ڵ������ֻ��һ�ε�ͼ���·���㷨:ͼΪ��ս������ƾ���P191��ʾ

#define MAX_N 15//���n,�˴�Ϊ 2<<n<<15
#define INF INT_MAX

int dp[1 << MAX_N][MAX_N];//��̬�滮�õ�����,������ߵ�����״̬֮������ʣ��ȫ������Ҫ�����·��

//�����INF��Ӳ�������ļӷ�
inline int add(int a, int b) {
	if (a == INF || b == INF)
		return INF;
	return a + b;
}

//�����ʼͼ,�ѷ��ʵ㼯��,���ڵ�λ��,����λ��,���ش������ʣ�໹��Ҫ�ߵ����·������(������¼·����)
template<int N>
int go_must_and_only_once(int d[][N], int S, int v,int E) {
	//�Ѿ���ù���
	if (dp[S][v] != INF)
		return dp[S][v];
	if (S == (1 << N) - 1 && v == E)//����״̬�Ѿ�������,����Ҫ��������
		return dp[S][v]=0;
	int res = INF;
	for (int u = 0; u < N; u++) {
		if (!(S >> u & 1)) {//ѡ����һ��û�߹��Ľڵ�
			int n = add(d[v][u], go_must_and_only_once(d, S | 1 << u, u, E));
			if (res > n)
				res = n;
		}
	}
	return dp[S][v] = res;
}

int main3_4_1() {
	int n = 5;//��5������
	int d[5][5] = {//ͼ
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

	//�ӽڵ�0��ʼ,��ǰ�߹��ļ���Ϊ0,��β��0
	int l = go_must_and_only_once<5>(d, 0, start, start);
	cout << "The cost is:" << l << endl;


	return 0;

}