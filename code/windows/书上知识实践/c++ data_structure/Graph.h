#pragma once

#include "Stack.h"

#define INF INT_MAX

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型

template<typename Te>
struct Floyd {
	Te cost;//最短路径权重
	int path;//前驱
};

template < typename Tv, typename Te> //顶点类型、边类型
class Graph { //图Graph模板类
private:
	void reset() { //所有顶点、边的辅助信息复位
		for (int i = 0; i < n; i++) { //所有顶点的       
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; //状态，时间标签
			parent(i) = -1; priority(i) = INF; //（在遍历树中的）父节点，优先级数
			for (int j = 0; j < n; j++) //所有边的
			if (exists(i, j)) type(i, j) = UNDETERMINED; //类型
		}
	}
	void BFS(int v, int& clock); //(连通域)广度优先搜索算法,Breadth First Search
	void DFS(int v, int& clock); //(连通域)深度优先搜索算法,Depth First Search
	void BCC(int v, int& clock, Stack<int>& S); //(连通域)基于DFS的双连通分量分解算法,bi-connected component
	bool TSort(int v, int& clock, Stack<Tv>* S); //(连通域)基于DFS的拓扑排序算法,topology sort
	template <typename PU> void PFS(int s, PU prioUpdater); //(连通域)优先级搜索框架,priority first search
public:
	// 顶点
	int n; //顶点总数
	virtual int insert(Tv const&) = 0; //插入顶点，返回编号
	virtual Tv remove(int) = 0; //删除顶点及其关联边，返回该顶点信息
	virtual Tv& vertex(int) = 0; //顶点v的数据(该顶点的确存在)
	virtual int inDegree(int) = 0; //顶点v的入度(该顶点的确存在)
	virtual int outDegree(int) = 0; //顶点v的出度(该顶点的确存在)
	virtual int firstNbr(int v) = 0; //顶点v的首个邻接顶点
	virtual int nextNbr(int v, int u) = 0; //顶点v的(相对于顶点j的)下一邻接顶点
	virtual VStatus& status(int v) = 0; //顶点v的状态
	virtual int& dTime(int) = 0; //顶点v的时间标签dTime
	virtual int& fTime(int) = 0; //顶点v的时间标签fTime
	virtual int& parent(int) = 0; //顶点v在遍历树中的父亲
	virtual int& priority(int) = 0; //顶点v在遍历树中的优先级数

	// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
	int e; //边总数
	virtual bool exists(int, int) = 0; //边(v, u)是否存在
	virtual void insert(Te const& edge, int w, int i, int j) = 0; //在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0; //删除顶点v和u之间的边e，返回该边信息
	virtual EType & type(int i, int j) = 0; //边(i, j)的类型
	virtual Te& edge(int i, int j) = 0; //边(i, j)的数据(该边的确存在)
	virtual int& cost(int i, int j) = 0;//返回边(i,j)的cost
	virtual int& weight(int i, int j) = 0; //边(i, j)的权重

	// 算法
	void bfs(int s); //广度优先搜索算法
	void dfs(int s); //深度优先搜索算法
	void bcc(int s); //基于DFS的双连通分量分解算法
	Stack<Tv>* tSort(int s); //基于DFS的拓扑排序算法

	void prim(int s); //(最小生成树)最小支撑树Prim算法,通过堆每个点做松弛
	void kruskal();//最小生成树Kruskal算法,通过贪心算法,每次最小的取未被发现的两点的边,不具体实现了,但复杂度是O(ElgE)

	bool bellman_ford(int s);//Bellman-Ford单源最短路径算法,适用于有边存在有负数权重,但如果存在一个负数环路,则返回false告知无解
	void dijkstra(int s); //(单源最短路径)最短路径Dijkstra算法

	template <typename PU> void pfs(int s, PU prioUpdater); //优先级搜索框架

	//所有节点对最短路径算法
	Te* slow_all_pair_shortest_paths(Te* twoD_arr);//通过矩阵来表示所有节点对的最短路径,传入n*n的矩阵,适用于有负数的图,O(n^4)
	Floyd<Te>* Floyd_Warshall(Floyd<Te>* twoD_arr);//弗洛伊德所有节点对最短路径算法,O(n^3)
	void log_FloudMartrix(Floyd<Te>* arr,int k);//传入n*n矩阵,和当前的k值

	//旅行商问题,每个节点走一次的最短路径(求最长路径应该也可以用这个方法,即状态压缩DP)
	int tsp(int v);//旅行商问题(traveling salesman problem),即从S回到S,并且每个点只能走一次,求最短路径的图算法,传入参数为起始点
	int _TSP(int *dp,int S, int v, int E);//旅行商问题内部用函数,传入参数为dp数组(记录当前集合当前点情况下,回到E的最短路径)

	//最大流问题,默认无环图
	//Ford-Fulkerson的dsp寻找增广路径算法,O(fE)
	Tv augmenting_path(int from, int to);//判断这条路能否被增广,若不能增广,返回0,否则返回这条路能增广的流量
	bool forward_augmenting_path(int from, int to);//判断一条可增广路径是正向可增广还是逆向可增广
	Tv Ford_Fulkerson(int s,int f);//Ford-Fulkerson最大流算法,其实Ford-Fulkerson没有说明寻找增广路径的算法,但默认此算法是通过深度优先搜索寻找的,O(fE),当有一条边最大流量是1时,逆向增广这条边会导致增广次数达到O(f)
	Tv Ford_Fulkerson_dsp(int v,int f,int flow);//Ford_Fulkerson用的深度优先搜索算法,传入当前点,终点,返回此次路径上的流
	//Edmonds-Karps的bfs寻找增广路径算法,O(V*E^2)
	Tv Edmonds_Karps(int s, int f);//Edmonds Karps算法,通过bfs寻找增广路径,由于每一条单向边u->v成为关键边后,起码路径长度+2才能再次成为关键边,路径长度无法超过V-1,每个增广路径必定存在一条单向边,由于是广度搜索,路径长度不可能变小,所以增广路径=关键边数量不超过E*(V-1)/2,每次bfsO(V+E),所以复杂度为O(V*E^2)
	Tv Edmonds_Karps_bfs(int v, int f, int flow);
	//Dinic算法,通过bfs先确定分层,然后用dfs在只向由bfs确定的层数变大的方向寻找增广路径,每次此分层结构没有路径能到时,就重新分层,直到bfs不能找到通向f的路径时
	//......具体的不实现了,挑战程序设计竞赛P217
	//最小费用流问题
	int min_cost_flow(int s, int f, int flow);//最小费用流问题,此处用Bellman-Ford的算法,由于每次最少flow-1,每次Bellman-ford算法时间O(VE),所以总共O(fVE)

};

template<typename Tv, typename Te>
struct PrimPU{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {//图,中心点,邻居
		if (UNDISCOVERED == g->status(v))
			if (g->priority(uk) > g->weight(uk,v)) {
				g->priority(uk) = g->weight(uk,v);
				g->parent(v) = uk;
			}
	}
};

template<typename Tv, typename Te>
struct DijkstraPU {
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {//图,中心点,邻居
		if (UNDISCOVERED == g->status(v))
			if (g->priority(v) > g->weight(uk, v)+g->priority(uk)) {//如果邻居的优先级数值被标的过大
				g->priority(v) = g->weight(uk, v) + g->priority(uk);//则把他改成正常的
				g->parent(v) = uk;
			}
	}
};

//处理加INF时会溢出的问题
int add(int a, int b) {
	if (a == INF || b == INF)
		return INF;
	return a + b;
}

#include "Graph_inplenmentation.h"