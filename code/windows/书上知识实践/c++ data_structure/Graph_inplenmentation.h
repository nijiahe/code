#include "Graph.h"
#include "Queue.h"

#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>

template <typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v, int& clock) { //（连通域）广度优先搜索算法
	Queue<int> q;
	status(v) = DISCOVERED;
	q.enqueue(v);
	while (!q.empty()) {
		int v = q.dequeue();
		dTime(v) == ++clock;
		for (int u = firstNbr(v);-1 < u; u = nextNbr(v, u)) {
			if (status(u) == UNDISCOVERED) {
				q.enqueue(u);
				status(u) = DISCOVERED;
				type(v, u) = TREE;//将边的属性设置为 被用到的树边
				parent(u) = v;//设置顶点u的父节点为v
			}
			else {
				type(v, u) = CROSS;//设置边的属性为  未用到,可忽略
			}
		}
		status(v) = VISITED;
	}
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) { //广度优先搜索算法,解决了不止一个连通域的问题
	int v = s; int clock = 0;
	reset();
	do {
		if(status(v)==UNDISCOVERED)
			BFS(v, clock);
	} while (s != (v = (++v) % n));//精妙,从s+1,s+2,s+3...n,0,1,2,...直到循环到s-1
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) { //(连通域)深度优先搜索算法,Depth First Search
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED://u尚未发现
			type(v, u) = TREE; parent(u) = v; DFS(u, clock);
			break;
		case DISCOVERED://u已被发现,但未访问完毕,此时后代指向了祖先
			type(v, u) = BACKWARD; 
			break;
		default://(VISITED,有向图)u已访问完毕,这样虽然v指向了u,但由于u已经回溯完毕,
			//若dTime v<u,则代表v和u在一条路上,u在v前面,只不过访问的时候绕了路,所以是向前FORWARD
			//若dTime v>u,则代表u早就被访问了,v是后来才访问的,则着眼于起点s来说,v和u是表兄弟关系(不是亲兄弟),所以边为CROSS,即跨边,需要跨越血缘障碍
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED; fTime(v) = ++clock;
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
	int v = s; int clock = 0;
	reset();
	do {
		DFS(v,clock);
	} while (s != (v = ++v%n));
}

template < typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {//(连通域)基于DFS的拓扑排序算法
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			type(v, u) = TREE;
			parent(u) = v;
			if (!TSort(u, clock, S))
				return false;
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			return false;//这里表示遇到环路了
		default://VISITED
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));
	fTime(v) = ++clock;//其实在拓扑排序算法中,fTime可以不记录
	return true;
}

template < typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {//基于DFS的拓扑排序算法
	reset();
	Stack<Tv>* S = new Stack<Tv>;
	int clock = 0;
	int v = s;
	do {
		if (status(v) = UNDISCOVERED)
			if (!TSort(v, clock, S))//如果TSort返回false,说明有环路,无法构成拓扑序列
				while (!S->empty())//则把栈S中的内容弹光,返回一个空S
					S->pop();
		break;
	} while (s != (v = ++v%n));
	
	return S;
}

#define hca(x) (fTime(x))//此处利用闲置的fTime来记录hca:higest connected ancestor
template < typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) { //(连通域)基于DFS的双连通分量分解算法
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);
			if (hca(u) < dTime(v))//如果子代拥有指向祖先的回路
				hca(v) = std::min(hca(u), hca(v));//则v也拥有指向祖先的回路
			else {//否则代表v的子代一直向前,没有回头路
				while (v != S.pop());//将v后代的关节点都取出
				S.push(v);//只存v这个最祖先的关节点就行了
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			if (parent(v) != u)//如果当前道路不是指向来时的路的
				hca(v) = std::min(hca(v), dTime(u));//就判断u是否为祖先,并且u这个祖先是否比现在存的祖先还要返祖
			break;
		default://VISITED
			type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
}
#undef hca

template < typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s) { //基于DFS的双连通分量分解算法
	reset();
	int clock = 0;
	Stack<Tv> S;
	int v = s;
	do {
		if (status(v) == DISCOVERED) {
			BCC(v, clock, S);
			S.pop();
		}
	} while (s != (v = (++v%n)));
}

template < typename Tv, typename Te>template <typename PU> 
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	while (1) {
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w))//枚举s的所有邻居
			prioUpdater(this, s, w);//更新所有邻居的优先级以及父节点
		for(int shortest=INT_MAX,w=0;w<n;w++)//遍历所有的顶点
			if(status(w)==UNDISCOVERED)//在尚未被发现的顶点中
				if (shortest > priority(w)) {//如果比当前的优先级更大(priority数值更大表示代价更大,优先级反而更小)
					shortest = priority(w);
					s = w;//转移到下个优先级更大的顶点继续循环
				}
		if (status(s) == VISITED)break;//如果没有比当前顶点优先级更大的,则中止循环
		status(s) = VISITED; type(parent(s), s) = TREE;
	}
}


template < typename Tv, typename Te>template <typename PU> 
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
	reset(); int v = s;
	do {
		if(status(v)==UNDISCOVERED)
			PFS(s, prioUpdater);
	} while (s != (v = (++v%n)));
}

//这种算法的时间是O(V^2+V^2),因为用的是邻接矩阵,若用邻接链表,并且使用优先级队列存储顶点,则只需要O(VlgV+ElgV)
template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) { //最小支撑树Prim算法
	reset(); priority(s) = 0;
	for (int i = 0; i < n; i++) { //共需引入n个顶点和n-1条边
		status(s) = VISITED;
		if (-1 != parent(s)) 
			type(parent(s), s) = TREE; //引入当前的s
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //枚举s的所有邻居j
			if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) //对邻接顶点j做松弛
			{
				priority(j) = weight(s, j); 
				parent(j) = s;
			} //与Dijkstra算法唯一的不同之处
		for (int shortest = INT_MAX, j = 0; j < n; j++) //选出下一极短跨边,若用优先级队列存放,则此步只需要O(lgV)
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j))){
				shortest = priority(j); 
				s = j;
			}
	}
}

//由于此处需要元素为edge的优先级队列,但不知道如何简易实现,所以不实现了,但是复杂度是O(ElgE)
/*template<typename Tv, typename Te>
void Graph<Tv, Te>::kruskal() {//最小生成树Kruskal算法
	reset(); 
	std::priority_queue<Te,std::greater<Te>> pq;//升序优先级队列
	std::map<Te, std::pair<int,int>> m;
	for (int i = 0; i < n; i++)//将所有的边构成一个优先级队列
		for (int j = 0; j < n; j++) 
			if (edge(i, j)){
				pq.push(weight(i, j));
				m.insert(std::make_pair((i, j), std::pair<int,int>(i, j)));
			}
				

	while (!pq.empty()) {
		Te p = pq.top(); pq.pop();//获得当前最小权重边
		
	}
}
*/

//O(VE)
template < typename Tv, typename Te>
bool Graph<Tv, Te>::bellman_ford(int s) {
	reset(); priority(s) = 0;
	int time = 0;//循环次数
		while (true) {//最多循环V-1次,超过了就代表存在负环,会无限循环下去,因为每次起码可以确定一条relax正确的边,最多有v-1条边,所以最多v-1次就可以保证全部relax完毕
		bool update = false;//标记这一次循环是否有更新,即是否还有需要更新的边,是否每个顶点都已经达到了最好的松弛
		for(int i = 0; i < n; i++)//其实这里应该是遍历所有的边,但由于此处用的是邻接矩阵,若为邻接链表,实际应为O(E)
			for (int j = 0; j < n; j++) {
				if (exists(i, j) && vertex(i) != INT_MAX && priority(j) > priority(i) + weight(i, j)) {//边存在,并且起点已经被初始化,并且需要更新
					priority(j) = priority(i) + weight(i, j);
					parent(j) = i;
					update = true;
				}
			}
		time++;//time==n-1的时候,若不存在负环,必定已经完毕,若还进行了
		if (!update)//如果该轮未更新,则以后也不会更新了,退出循环
			return true;
		if (time > n - 1)//如果v-1次循环结束,还会循环,表示存在负环,则无解
			return false;
	}
}

//此处算法为O(V^2),若顶点V用优先级队列保存,则时间为O(VlgV)
template < typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {//最短路径Dijkstra算法
	reset();
	priority(s) = 0;
	for (int i = 0; i < n; i++) {
		status(s) = VISITED;
		if (parent(s) != -1)
			type(parent(s), s) = TREE;
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //遍历所有邻居,共O(E)
			if ((status(j) == UNDISCOVERED)&&(priority(j)>priority(s)+weight(s,j))) {//如果邻居的优先级数量值不是最小的
				priority(j) = priority(s) + weight(s, j);//更新它
				parent(j) = s;
			}
		for (int shortest = INT_MAX, j = 0; j < n; j++) //遍历所有节点,选择其中未发现的
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j))){ //选出未被发现的节点中的最短路径
				shortest = priority(j); //
				s = j; 
			}
	}
}

//计算所有节点对之间的最短路径,O(n^4),可改进,只需算出L(1),L(2),L(4),L(8)...在将n进行分解即可
//比如n=15,则L(13)=cal(L(1),L(4),L(8)),这样只需要O(N^3lgn)
template < typename Tv, typename Te>
Te* Graph<Tv, Te>::slow_all_pair_shortest_paths(Te* arr) {
	Te* T1 = new Te[n*n], *T2 = new Te[n*n];
	for (int i = 0; i < n; i++) {//初始化,保存最多一条边的最短路径
		for (int j = 0; j < n; j++) {
			arr[n*i+j] = exists(i, j) ? weight(i, j) : (i==j?0:INT_MAX);
			T1[n*i + j] = arr[n*i + j];
		}
	}
	Te* use = T1, *temp = T2;//use表示当前存着数据的,temp表示用来存放求解出来的数据的
	for (int i = 2; i <= n - 1; i++) {//从两条边循环到n-1条边
		for (int i = 0; i < n; i++)
			for (int j = 0; i < n; j++) {//每个二维矩阵的元素
				temp[i*n + j] = INT_MAX;
				for (int k = 0; k < n; k++) {//需要取n次计算的最小值,即min(use[i,k]+arr[k,j]),即i-1条边的最短路径和加上一条边的最短路径之和最小
					if (arr[i*n + k] != INT_MAX && arr[k*n + j] != INT_MAX && (temp[i*n + j] > use[i*n + k] + arr[k*n + j]))
						temp[i*n + j] = arr[i*n + k] + arr[k*n + j];//更新
				}
			}
		std::swap(arr, temp);//交换use和temp的指向
	}
	//返回前的操作,将结果复制到要返回的数组中
	for (int i = 0; i < n*n; i++) {
		arr[i] = use[i];
	}
	
	delete[]T1; delete[]T2;
	return arr;
}

//费洛伊德所有节点对最短路径算法,O(V^3),适用于负数图,稠密图情况下与Bellman-Ford的单源最短路径算法O(VE)渐进相同
//原理:动态规划,一开始初始化为不存在中间节点,之后慢慢加入允许的中间节点
//第k个矩阵记录了允许前k个顶点作为中间节点的两个节点之间的最短路径,因此就算是k之后的节点,也存有路径,只不过路径上只有1-k,之后需要在更新
//输入:n*n的Floyd空数组,保存最短路径权重和前驱矩阵,算法在其中填写i->j的最短路径权重
/*
前驱矩阵介绍:i->j的途中若有中间节点,前驱矩阵对应位置保存j前一个节点
			 i->j的途中若没有中间节点,前驱矩阵保存i
			 若i==j或者i->j不存在路径,则保存INT_MAX
*/
template < typename Tv, typename Te>
Floyd<Te>* Graph<Tv, Te>::Floyd_Warshall(Floyd<Te>* twoD_arr) {
#ifdef _DEBUG
	std::cout << "开始调试Floyd节点对最短路径矩阵" << std::endl;
#endif
	//初始化不存在任何中间节点的情况
	for(int i = 0;i < n; i++)
		for (int j = 0; j < n; j++) {
			if (exists(i, j)) {
				twoD_arr[i*n + j].cost = weight(i, j);
				twoD_arr[i*n + j].path = i;
			}
			else if (i == j) {
				twoD_arr[i*n + j].cost = 0;
				twoD_arr[i*n + j].path = INT_MAX;
			}
			else {//无路径
				twoD_arr[i*n + j].cost = INT_MAX;//作为无穷大来使用
				twoD_arr[i*n + j].path = INT_MAX;
			}
		}
#ifdef _DEBUG
	log_FloudMartrix(twoD_arr, -1);
#endif
	Floyd<Te>* use = twoD_arr;
	Floyd<Te>* temp = new Floyd<Te>[n*n];
	for (int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (use[i*n + k].cost != INT_MAX && use[k*n + j].cost != INT_MAX && use[i*n + j].cost > use[i*n + k].cost + use[k*n + j].cost) {//选用k作为中间节点后花费会变少
					temp[i*n + j].cost = use[i*n + k].cost + use[k*n + j].cost;
					temp[i*n + j].path = use[k*n + j].path;//i->j的前驱等于k->j的前驱
				}
				else{
					temp[i*n + j].cost = use[i*n + j].cost;
					temp[i*n + j].path = use[i*n + j].path;
				}
			}
#ifdef _DEBUG
		//打印调试信息
		log_FloudMartrix(temp, k);
#endif
		std::swap(use, temp);
	}
	//返回
	if (use != twoD_arr)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				twoD_arr[i*n + j] = use[i*n + j];
			}

#ifdef _DEBUG
	//根据前驱矩阵打印路径
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++) {
			std::cout << "The path of " << i << " to " << j << " is:";
			int path = j;
			if (use[i*n + j].path == INT_MAX)//没有路径
				std::cout << "∞" << std::endl;
			else {//用栈取出路径
				Stack<int> s;
				do {
					s.push(use[i*n + path].path);
					path = use[i*n + path].path;
				} while (path!=i);
				while (!s.empty())
					std::cout << s.pop() << "->";
				std::cout << j << std::endl;
			}
		}
#endif // _DEBUG
	
	delete[]use;
	return twoD_arr;
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::log_FloudMartrix(Floyd<Te>* arr,int k) {
	std::cout << "权重矩阵D(" << k << "):" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(arr[i*n+j].cost==INT_MAX)
				std::cout << std::setw(3) << "∞" ;
			else
				std::cout << std::setw(3) << arr[i*n + j].cost;
		}
		std::cout << std::endl;
	}
	std::cout << "前驱矩阵P(" << k << "):" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i*n + j].path == INT_MAX)
				std::cout << std::setw(3) << "∞";
			else
				std::cout << std::setw(3) << arr[i*n + j].path;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template < typename Tv, typename Te>
int Graph<Tv, Te>::tsp(int v) {//旅行商问题,即从S回到S,并且每个点只能走一次,求最短路径的图算法
	Te* dp = new Te[(1<<n)*n];
	for (int i = 0; i < (1 << n)*n; i++)
		dp[i] = INF;
	int num = _TSP(dp, 0, v, v);
	delete[]dp;
	return num;
}

//传入参数:dp数组,当前访问过的顶点集合S,当前所在v,终点E,返回在此状态下完成旅行商问题需要的剩余代价,O(n^2*2^n)
template < typename Tv, typename Te>
int Graph<Tv, Te>::_TSP(int* dp,int S, int v, int E) {//旅行商问题内部用函数
	if (dp[S*n+v] !=INF)//如果已求得,直接返回即可
		return dp[S*n + v];
	if (S == (1 << n) - 1 && v == E)//已到终点,则返回
		return dp[S*n + v] = 0;
	int res = INF;//默认为INF的花费
	for(int u=0;u<n;u++)
		if (!((S >> u) & 1)) {//寻找下一未走过的点
			res = std::min(res, add(exists(v, u) ? weight(v, u) : INF, _TSP(dp, S | (1 << u), u, E)));
		}
	return dp[S*n + v] = res;
}

//Ford-Fulkerson最大流算法,其实Ford-Fulkerson没有说明寻找增广路径的算法,但默认此算法是通过深度优先搜索寻找的
//传入参数:起点,终点,返回最大流
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Ford_Fulkerson(int s, int f) {
	//先将所有点和边的data置为0,因为data要用来保存流量
	for (int i = 0; i < n; i++) {
		vertex(i) = 0;
		for (int j = 0; j < n; j++) {
			if (exists(i, j))
				edge(i, j) = 0;
		}
	}
	int num = 0;
	while (true) {//当还存在增广路径时,解析这条增广路径,修改路径上的边和顶点上的流量
		reset();
		int d = Ford_Fulkerson_dsp(s, f, INF);
		if (d == 0)
			break;
		else
			num += d;
	}


	return num;//或者返回vertex(f)也行
}

//若v->f有增广路径,则返回flow,否则返回0
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Ford_Fulkerson_dsp(int v, int f,int flow) {//Ford_Fulkerson用的深度优先搜索算法,传入当前点,终点,到目前节点为止的最大流
	status(v) = VISITED;
	int res = 0;//若找到路径,这个值会被修改为路径上的最大流,否则返回0
	if (v == f) {//寻找到一条路径,分析路径
		res = flow;
	}
	else
		for (int i = 0; i < n;i++) {//寻找所有的可用增广路,即v->i有路并且未到流量上限,或者i->v有路并且存在流量
			if (status(i) != VISITED) {
				int n1 = augmenting_path(v, i);
				if (n1 > 0) { //如果可增广
					if ((res = Ford_Fulkerson_dsp(i, f, std::min(n1, flow))) > 0) {//找到路径,直接break即可
						if (forward_augmenting_path(v,i)) {//正向
							vertex(i) += res;
							edge(v, i) += res;
						}
						else {//逆向
							edge(i, v) -= res;
						}
						break;
					}			
				}			
			}
		}
	return res;
}

template < typename Tv, typename Te>
Tv Graph<Tv, Te>::augmenting_path(int from, int to) {
	if (exists(from, to) && edge(from, to) < weight(from, to)) //正向边,并且容量未到上限
		return  weight(from, to) - edge(from, to);
	else if(exists(to,from)&&edge(to, from) > 0)//逆向边,并且可逆向增广
		return edge(to,from);
	else return 0;//无法增广
}

template < typename Tv, typename Te>
bool Graph<Tv, Te>::forward_augmenting_path(int from, int to) {
	if (exists(from, to) && edge(from, to) < weight(from, to)) //正向边,并且容量未到上限
		return true;
	else
		return false;
}

//Edmonds-Karps算法,通过bfs寻找增广路径,
/*
原理:由于每一条单向边u->v成为关键边后,起码路径长度+2才能再次成为关键边,路径长度无法超过V-1/
每个增广路径必定存在一条单向边,由于是广度搜索,路径长度不可能变小,所以增广路径=关键边数量不超过E*(V-1)/2
每次bfsO(V+E),所以复杂度为O(V*E^2)
//输入:源点,汇点,输出:最大流
*/
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Edmonds_Karps(int s, int f) {
	int num = 0;
	for (int i = 0; i< n; i++) {
		vertex(i) = 0;
		for (int j = 0; j < n; j++) {
			if (exists(i, j))
				edge(i, j) = 0;
		}
	}
	while (true) {
		reset();
		int n1 = Edmonds_Karps_bfs(s, f, INF);
		if (n1 == 0)//已经不存在增广路径了
			break;
		else
			num += n1;
	}
	return num;//或者vertex(f)也行,因为此算法会在每个点和边记录其流量

}

//输入:当前位置,汇点,到当前位置为止的流,返回试图从此条路径到f的最大流(如果返回0代表此条路径不通)
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Edmonds_Karps_bfs(int v, int f, int flow) {
	status(v) = VISITED;
	if (v == f)
		return flow;
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (status(i) != VISITED) {
			int n1 = augmenting_path(v, i);
			if (n1 > 0) {//可增广
				if ((res = Edmonds_Karps_bfs(i, f, std::min(n1, flow))) > 0) {//沿着此增广,有路径能到f
					if (forward_augmenting_path(v,i)) {//正向边
						vertex(i) += res;
						edge(v, i) += res;
					}
					else //反向边
						edge(i, v) -= res;
					break;
				}
			}
		}
	}
	return res;
}

//传入参数:源点,汇点,要传输的流量数量,返回花费,若返回-1表示不存在路使得能传输flow这么多的流量,或存在负环路
template <typename Tv, typename Te>
int Graph<Tv, Te>::min_cost_flow(int s, int f,int flow) {//最小费用流问题,由于逆向边花费为负数,因此只能使用Bellman-Ford的算法,而不能使用Dijkstra的
	//对所有的点、边上记载的流量进行初始化
#ifdef _DEBUG
	std::cout << "开始调试最小费用流问题:" << std::endl;
#endif
	for (int i = 0; i < n; i++) {
		vertex(i) = 0;
		for (int j = 0; j < n; j++) {
			if (exists(i, j))
				edge(i, j) = 0;
		}
	}
	int cos = 0;
	//循环的寻找路径来传输flow数量的流量
	while (flow > 0) {
		reset();//清除上一次Bellman-ford算法留下的路径s
		priority(s) = 0;
		//通过Bellman-Ford的方法找到一条最短增广路径
		bool update = true;
		int times = 0;
		while (update) {
			update = false;
			for (int i = 0; i < n; i++)//遍历所有的增广路径
				for (int j = 0; j < n; j++) {
					if (j == s)continue;//s不能被流入
					if (i == f)continue;//f不能被流出
					if (priority(i)!=INF&&augmenting_path(i, j)) {//已发现,并且可增广
#if 0
						//打印所有的priority:
						for (int i = 0; i < n; i++)
							std::cout << "p" << i << " is " << priority(i) << ",";
						std::cout << std::endl;
#endif
						if (forward_augmenting_path(i, j)) {//正向边
							if (priority(j) > priority(i) + cost(i, j)) {//费用可更新的更低
								priority(j) = priority(i) + cost(i, j);
								parent(j) = i;
								update = true;
							}
						}
						else {//反向边
							if (priority(j) > priority(i) - cost(j, i)) {//费用可更新的更低
								priority(j) = priority(i) - cost(j, i);
								parent(j) = i;
								update = true;
							}
						}
					}
				}
			
			if (times == n - 1)//存在负环
				return -1;
			times++;
		}
		//Bellman-Ford算法已经找到花费最少的增广路
		if (parent(f) == -1)//若在flow还有剩余时就没有增广路了,返回-1
			return -1;

		int fl = flow; int temp = f;
#ifdef _DEBUG
		Stack<int> sk;
#endif
		//在这条现在的最小费用路上
		while (temp != s) {
			fl = std::min(fl, augmenting_path(parent(temp), temp));//计算此条路上需要通过的流量
#ifdef _DEBUG
			sk.push(parent(temp));
#endif
			temp = parent(temp);
		}
		flow -= fl;
		cos += fl * priority(f);//累计费用,若遇到反向路也会返还不走反向路的钱
		temp = f;
		while (temp != s) {//再次遍历这条路径,更新点、边上的流量信息
			if (forward_augmenting_path(parent(temp), temp)) {//正向增广路径
				vertex(temp) += fl;
				edge(parent(temp), temp) += fl;
			}
			else //反向增广路径
				edge(temp, parent(temp)) -= fl;
			temp = parent(temp);
		}
#ifdef _DEBUG
		//打印调试信息
		std::cout << "The path is:";
		while (!sk.empty())
			std::cout << sk.pop() << "->";
		std::cout << f << ",and flow is " << fl << ",unit-price of flow is " << priority(f) << std::endl;
#endif
	}
	return cos;
}