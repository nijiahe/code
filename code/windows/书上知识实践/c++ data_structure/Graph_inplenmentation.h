#include "Graph.h"
#include "Queue.h"

#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>

template <typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v, int& clock) { //����ͨ�򣩹�����������㷨
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
				type(v, u) = TREE;//���ߵ���������Ϊ ���õ�������
				parent(u) = v;//���ö���u�ĸ��ڵ�Ϊv
			}
			else {
				type(v, u) = CROSS;//���ñߵ�����Ϊ  δ�õ�,�ɺ���
			}
		}
		status(v) = VISITED;
	}
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) { //������������㷨,����˲�ֹһ����ͨ�������
	int v = s; int clock = 0;
	reset();
	do {
		if(status(v)==UNDISCOVERED)
			BFS(v, clock);
	} while (s != (v = (++v) % n));//����,��s+1,s+2,s+3...n,0,1,2,...ֱ��ѭ����s-1
}

template < typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) { //(��ͨ��)������������㷨,Depth First Search
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED://u��δ����
			type(v, u) = TREE; parent(u) = v; DFS(u, clock);
			break;
		case DISCOVERED://u�ѱ�����,��δ�������,��ʱ���ָ��������
			type(v, u) = BACKWARD; 
			break;
		default://(VISITED,����ͼ)u�ѷ������,������Ȼvָ����u,������u�Ѿ��������,
			//��dTime v<u,�����v��u��һ��·��,u��vǰ��,ֻ�������ʵ�ʱ������·,��������ǰFORWARD
			//��dTime v>u,�����u��ͱ�������,v�Ǻ����ŷ��ʵ�,�����������s��˵,v��u�Ǳ��ֵܹ�ϵ(�������ֵ�),���Ա�ΪCROSS,�����,��Ҫ��ԽѪԵ�ϰ�
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
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {//(��ͨ��)����DFS�����������㷨
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
			return false;//�����ʾ������·��
		default://VISITED
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));
	fTime(v) = ++clock;//��ʵ�����������㷨��,fTime���Բ���¼
	return true;
}

template < typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {//����DFS�����������㷨
	reset();
	Stack<Tv>* S = new Stack<Tv>;
	int clock = 0;
	int v = s;
	do {
		if (status(v) = UNDISCOVERED)
			if (!TSort(v, clock, S))//���TSort����false,˵���л�·,�޷�������������
				while (!S->empty())//���ջS�е����ݵ���,����һ����S
					S->pop();
		break;
	} while (s != (v = ++v%n));
	
	return S;
}

#define hca(x) (fTime(x))//�˴��������õ�fTime����¼hca:higest connected ancestor
template < typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) { //(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
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
			if (hca(u) < dTime(v))//����Ӵ�ӵ��ָ�����ȵĻ�·
				hca(v) = std::min(hca(u), hca(v));//��vҲӵ��ָ�����ȵĻ�·
			else {//�������v���Ӵ�һֱ��ǰ,û�л�ͷ·
				while (v != S.pop());//��v����Ĺؽڵ㶼ȡ��
				S.push(v);//ֻ��v��������ȵĹؽڵ������
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			if (parent(v) != u)//�����ǰ��·����ָ����ʱ��·��
				hca(v) = std::min(hca(v), dTime(u));//���ж�u�Ƿ�Ϊ����,����u��������Ƿ�����ڴ�����Ȼ�Ҫ����
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
void Graph<Tv, Te>::bcc(int s) { //����DFS��˫��ͨ�����ֽ��㷨
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
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w))//ö��s�������ھ�
			prioUpdater(this, s, w);//���������ھӵ����ȼ��Լ����ڵ�
		for(int shortest=INT_MAX,w=0;w<n;w++)//�������еĶ���
			if(status(w)==UNDISCOVERED)//����δ�����ֵĶ�����
				if (shortest > priority(w)) {//����ȵ�ǰ�����ȼ�����(priority��ֵ�����ʾ���۸���,���ȼ�������С)
					shortest = priority(w);
					s = w;//ת�Ƶ��¸����ȼ�����Ķ������ѭ��
				}
		if (status(s) == VISITED)break;//���û�бȵ�ǰ�������ȼ������,����ֹѭ��
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

//�����㷨��ʱ����O(V^2+V^2),��Ϊ�õ����ڽӾ���,�����ڽ�����,����ʹ�����ȼ����д洢����,��ֻ��ҪO(VlgV+ElgV)
template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) { //��С֧����Prim�㷨
	reset(); priority(s) = 0;
	for (int i = 0; i < n; i++) { //��������n�������n-1����
		status(s) = VISITED;
		if (-1 != parent(s)) 
			type(parent(s), s) = TREE; //���뵱ǰ��s
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //ö��s�������ھ�j
			if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) //���ڽӶ���j���ɳ�
			{
				priority(j) = weight(s, j); 
				parent(j) = s;
			} //��Dijkstra�㷨Ψһ�Ĳ�֮ͬ��
		for (int shortest = INT_MAX, j = 0; j < n; j++) //ѡ����һ���̿��,�������ȼ����д��,��˲�ֻ��ҪO(lgV)
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j))){
				shortest = priority(j); 
				s = j;
			}
	}
}

//���ڴ˴���ҪԪ��Ϊedge�����ȼ�����,����֪����μ���ʵ��,���Բ�ʵ����,���Ǹ��Ӷ���O(ElgE)
/*template<typename Tv, typename Te>
void Graph<Tv, Te>::kruskal() {//��С������Kruskal�㷨
	reset(); 
	std::priority_queue<Te,std::greater<Te>> pq;//�������ȼ�����
	std::map<Te, std::pair<int,int>> m;
	for (int i = 0; i < n; i++)//�����еı߹���һ�����ȼ�����
		for (int j = 0; j < n; j++) 
			if (edge(i, j)){
				pq.push(weight(i, j));
				m.insert(std::make_pair((i, j), std::pair<int,int>(i, j)));
			}
				

	while (!pq.empty()) {
		Te p = pq.top(); pq.pop();//��õ�ǰ��СȨ�ر�
		
	}
}
*/

//O(VE)
template < typename Tv, typename Te>
bool Graph<Tv, Te>::bellman_ford(int s) {
	reset(); priority(s) = 0;
	int time = 0;//ѭ������
		while (true) {//���ѭ��V-1��,�����˾ʹ�����ڸ���,������ѭ����ȥ,��Ϊÿ���������ȷ��һ��relax��ȷ�ı�,�����v-1����,�������v-1�ξͿ��Ա�֤ȫ��relax���
		bool update = false;//�����һ��ѭ���Ƿ��и���,���Ƿ�����Ҫ���µı�,�Ƿ�ÿ�����㶼�Ѿ��ﵽ����õ��ɳ�
		for(int i = 0; i < n; i++)//��ʵ����Ӧ���Ǳ������еı�,�����ڴ˴��õ����ڽӾ���,��Ϊ�ڽ�����,ʵ��ӦΪO(E)
			for (int j = 0; j < n; j++) {
				if (exists(i, j) && vertex(i) != INT_MAX && priority(j) > priority(i) + weight(i, j)) {//�ߴ���,��������Ѿ�����ʼ��,������Ҫ����
					priority(j) = priority(i) + weight(i, j);
					parent(j) = i;
					update = true;
				}
			}
		time++;//time==n-1��ʱ��,�������ڸ���,�ض��Ѿ����,����������
		if (!update)//�������δ����,���Ժ�Ҳ���������,�˳�ѭ��
			return true;
		if (time > n - 1)//���v-1��ѭ������,����ѭ��,��ʾ���ڸ���,���޽�
			return false;
	}
}

//�˴��㷨ΪO(V^2),������V�����ȼ����б���,��ʱ��ΪO(VlgV)
template < typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {//���·��Dijkstra�㷨
	reset();
	priority(s) = 0;
	for (int i = 0; i < n; i++) {
		status(s) = VISITED;
		if (parent(s) != -1)
			type(parent(s), s) = TREE;
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //���������ھ�,��O(E)
			if ((status(j) == UNDISCOVERED)&&(priority(j)>priority(s)+weight(s,j))) {//����ھӵ����ȼ�����ֵ������С��
				priority(j) = priority(s) + weight(s, j);//������
				parent(j) = s;
			}
		for (int shortest = INT_MAX, j = 0; j < n; j++) //�������нڵ�,ѡ������δ���ֵ�
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j))){ //ѡ��δ�����ֵĽڵ��е����·��
				shortest = priority(j); //
				s = j; 
			}
	}
}

//�������нڵ��֮������·��,O(n^4),�ɸĽ�,ֻ�����L(1),L(2),L(4),L(8)...�ڽ�n���зֽ⼴��
//����n=15,��L(13)=cal(L(1),L(4),L(8)),����ֻ��ҪO(N^3lgn)
template < typename Tv, typename Te>
Te* Graph<Tv, Te>::slow_all_pair_shortest_paths(Te* arr) {
	Te* T1 = new Te[n*n], *T2 = new Te[n*n];
	for (int i = 0; i < n; i++) {//��ʼ��,�������һ���ߵ����·��
		for (int j = 0; j < n; j++) {
			arr[n*i+j] = exists(i, j) ? weight(i, j) : (i==j?0:INT_MAX);
			T1[n*i + j] = arr[n*i + j];
		}
	}
	Te* use = T1, *temp = T2;//use��ʾ��ǰ�������ݵ�,temp��ʾ������������������ݵ�
	for (int i = 2; i <= n - 1; i++) {//��������ѭ����n-1����
		for (int i = 0; i < n; i++)
			for (int j = 0; i < n; j++) {//ÿ����ά�����Ԫ��
				temp[i*n + j] = INT_MAX;
				for (int k = 0; k < n; k++) {//��Ҫȡn�μ������Сֵ,��min(use[i,k]+arr[k,j]),��i-1���ߵ����·���ͼ���һ���ߵ����·��֮����С
					if (arr[i*n + k] != INT_MAX && arr[k*n + j] != INT_MAX && (temp[i*n + j] > use[i*n + k] + arr[k*n + j]))
						temp[i*n + j] = arr[i*n + k] + arr[k*n + j];//����
				}
			}
		std::swap(arr, temp);//����use��temp��ָ��
	}
	//����ǰ�Ĳ���,��������Ƶ�Ҫ���ص�������
	for (int i = 0; i < n*n; i++) {
		arr[i] = use[i];
	}
	
	delete[]T1; delete[]T2;
	return arr;
}

//�����������нڵ�����·���㷨,O(V^3),�����ڸ���ͼ,����ͼ�������Bellman-Ford�ĵ�Դ���·���㷨O(VE)������ͬ
//ԭ��:��̬�滮,һ��ʼ��ʼ��Ϊ�������м�ڵ�,֮����������������м�ڵ�
//��k�������¼������ǰk��������Ϊ�м�ڵ�������ڵ�֮������·��,��˾�����k֮��Ľڵ�,Ҳ����·��,ֻ����·����ֻ��1-k,֮����Ҫ�ڸ���
//����:n*n��Floyd������,�������·��Ȩ�غ�ǰ������,�㷨��������дi->j�����·��Ȩ��
/*
ǰ���������:i->j��;�������м�ڵ�,ǰ�������Ӧλ�ñ���jǰһ���ڵ�
			 i->j��;����û���м�ڵ�,ǰ�����󱣴�i
			 ��i==j����i->j������·��,�򱣴�INT_MAX
*/
template < typename Tv, typename Te>
Floyd<Te>* Graph<Tv, Te>::Floyd_Warshall(Floyd<Te>* twoD_arr) {
#ifdef _DEBUG
	std::cout << "��ʼ����Floyd�ڵ�����·������" << std::endl;
#endif
	//��ʼ���������κ��м�ڵ�����
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
			else {//��·��
				twoD_arr[i*n + j].cost = INT_MAX;//��Ϊ�������ʹ��
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
				if (use[i*n + k].cost != INT_MAX && use[k*n + j].cost != INT_MAX && use[i*n + j].cost > use[i*n + k].cost + use[k*n + j].cost) {//ѡ��k��Ϊ�м�ڵ�󻨷ѻ����
					temp[i*n + j].cost = use[i*n + k].cost + use[k*n + j].cost;
					temp[i*n + j].path = use[k*n + j].path;//i->j��ǰ������k->j��ǰ��
				}
				else{
					temp[i*n + j].cost = use[i*n + j].cost;
					temp[i*n + j].path = use[i*n + j].path;
				}
			}
#ifdef _DEBUG
		//��ӡ������Ϣ
		log_FloudMartrix(temp, k);
#endif
		std::swap(use, temp);
	}
	//����
	if (use != twoD_arr)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				twoD_arr[i*n + j] = use[i*n + j];
			}

#ifdef _DEBUG
	//����ǰ�������ӡ·��
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++) {
			std::cout << "The path of " << i << " to " << j << " is:";
			int path = j;
			if (use[i*n + j].path == INT_MAX)//û��·��
				std::cout << "��" << std::endl;
			else {//��ջȡ��·��
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
	std::cout << "Ȩ�ؾ���D(" << k << "):" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(arr[i*n+j].cost==INT_MAX)
				std::cout << std::setw(3) << "��" ;
			else
				std::cout << std::setw(3) << arr[i*n + j].cost;
		}
		std::cout << std::endl;
	}
	std::cout << "ǰ������P(" << k << "):" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i*n + j].path == INT_MAX)
				std::cout << std::setw(3) << "��";
			else
				std::cout << std::setw(3) << arr[i*n + j].path;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template < typename Tv, typename Te>
int Graph<Tv, Te>::tsp(int v) {//����������,����S�ص�S,����ÿ����ֻ����һ��,�����·����ͼ�㷨
	Te* dp = new Te[(1<<n)*n];
	for (int i = 0; i < (1 << n)*n; i++)
		dp[i] = INF;
	int num = _TSP(dp, 0, v, v);
	delete[]dp;
	return num;
}

//�������:dp����,��ǰ���ʹ��Ķ��㼯��S,��ǰ����v,�յ�E,�����ڴ�״̬�����������������Ҫ��ʣ�����,O(n^2*2^n)
template < typename Tv, typename Te>
int Graph<Tv, Te>::_TSP(int* dp,int S, int v, int E) {//�����������ڲ��ú���
	if (dp[S*n+v] !=INF)//��������,ֱ�ӷ��ؼ���
		return dp[S*n + v];
	if (S == (1 << n) - 1 && v == E)//�ѵ��յ�,�򷵻�
		return dp[S*n + v] = 0;
	int res = INF;//Ĭ��ΪINF�Ļ���
	for(int u=0;u<n;u++)
		if (!((S >> u) & 1)) {//Ѱ����һδ�߹��ĵ�
			res = std::min(res, add(exists(v, u) ? weight(v, u) : INF, _TSP(dp, S | (1 << u), u, E)));
		}
	return dp[S*n + v] = res;
}

//Ford-Fulkerson������㷨,��ʵFord-Fulkersonû��˵��Ѱ������·�����㷨,��Ĭ�ϴ��㷨��ͨ�������������Ѱ�ҵ�
//�������:���,�յ�,���������
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Ford_Fulkerson(int s, int f) {
	//�Ƚ����е�ͱߵ�data��Ϊ0,��ΪdataҪ������������
	for (int i = 0; i < n; i++) {
		vertex(i) = 0;
		for (int j = 0; j < n; j++) {
			if (exists(i, j))
				edge(i, j) = 0;
		}
	}
	int num = 0;
	while (true) {//������������·��ʱ,������������·��,�޸�·���ϵıߺͶ����ϵ�����
		reset();
		int d = Ford_Fulkerson_dsp(s, f, INF);
		if (d == 0)
			break;
		else
			num += d;
	}


	return num;//���߷���vertex(f)Ҳ��
}

//��v->f������·��,�򷵻�flow,���򷵻�0
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Ford_Fulkerson_dsp(int v, int f,int flow) {//Ford_Fulkerson�õ�������������㷨,���뵱ǰ��,�յ�,��Ŀǰ�ڵ�Ϊֹ�������
	status(v) = VISITED;
	int res = 0;//���ҵ�·��,���ֵ�ᱻ�޸�Ϊ·���ϵ������,���򷵻�0
	if (v == f) {//Ѱ�ҵ�һ��·��,����·��
		res = flow;
	}
	else
		for (int i = 0; i < n;i++) {//Ѱ�����еĿ�������·,��v->i��·����δ����������,����i->v��·���Ҵ�������
			if (status(i) != VISITED) {
				int n1 = augmenting_path(v, i);
				if (n1 > 0) { //���������
					if ((res = Ford_Fulkerson_dsp(i, f, std::min(n1, flow))) > 0) {//�ҵ�·��,ֱ��break����
						if (forward_augmenting_path(v,i)) {//����
							vertex(i) += res;
							edge(v, i) += res;
						}
						else {//����
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
	if (exists(from, to) && edge(from, to) < weight(from, to)) //�����,��������δ������
		return  weight(from, to) - edge(from, to);
	else if(exists(to,from)&&edge(to, from) > 0)//�����,���ҿ���������
		return edge(to,from);
	else return 0;//�޷�����
}

template < typename Tv, typename Te>
bool Graph<Tv, Te>::forward_augmenting_path(int from, int to) {
	if (exists(from, to) && edge(from, to) < weight(from, to)) //�����,��������δ������
		return true;
	else
		return false;
}

//Edmonds-Karps�㷨,ͨ��bfsѰ������·��,
/*
ԭ��:����ÿһ�������u->v��Ϊ�ؼ��ߺ�,����·������+2�����ٴγ�Ϊ�ؼ���,·�������޷�����V-1/
ÿ������·���ض�����һ�������,�����ǹ������,·�����Ȳ����ܱ�С,��������·��=�ؼ�������������E*(V-1)/2
ÿ��bfsO(V+E),���Ը��Ӷ�ΪO(V*E^2)
//����:Դ��,���,���:�����
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
		if (n1 == 0)//�Ѿ�����������·����
			break;
		else
			num += n1;
	}
	return num;//����vertex(f)Ҳ��,��Ϊ���㷨����ÿ����ͱ߼�¼������

}

//����:��ǰλ��,���,����ǰλ��Ϊֹ����,������ͼ�Ӵ���·����f�������(�������0�������·����ͨ)
template < typename Tv, typename Te>
Tv Graph<Tv, Te>::Edmonds_Karps_bfs(int v, int f, int flow) {
	status(v) = VISITED;
	if (v == f)
		return flow;
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (status(i) != VISITED) {
			int n1 = augmenting_path(v, i);
			if (n1 > 0) {//������
				if ((res = Edmonds_Karps_bfs(i, f, std::min(n1, flow))) > 0) {//���Ŵ�����,��·���ܵ�f
					if (forward_augmenting_path(v,i)) {//�����
						vertex(i) += res;
						edge(v, i) += res;
					}
					else //�����
						edge(i, v) -= res;
					break;
				}
			}
		}
	}
	return res;
}

//�������:Դ��,���,Ҫ�������������,���ػ���,������-1��ʾ������·ʹ���ܴ���flow��ô�������,����ڸ���·
template <typename Tv, typename Te>
int Graph<Tv, Te>::min_cost_flow(int s, int f,int flow) {//��С����������,��������߻���Ϊ����,���ֻ��ʹ��Bellman-Ford���㷨,������ʹ��Dijkstra��
	//�����еĵ㡢���ϼ��ص��������г�ʼ��
#ifdef _DEBUG
	std::cout << "��ʼ������С����������:" << std::endl;
#endif
	for (int i = 0; i < n; i++) {
		vertex(i) = 0;
		for (int j = 0; j < n; j++) {
			if (exists(i, j))
				edge(i, j) = 0;
		}
	}
	int cos = 0;
	//ѭ����Ѱ��·��������flow����������
	while (flow > 0) {
		reset();//�����һ��Bellman-ford�㷨���µ�·��s
		priority(s) = 0;
		//ͨ��Bellman-Ford�ķ����ҵ�һ���������·��
		bool update = true;
		int times = 0;
		while (update) {
			update = false;
			for (int i = 0; i < n; i++)//�������е�����·��
				for (int j = 0; j < n; j++) {
					if (j == s)continue;//s���ܱ�����
					if (i == f)continue;//f���ܱ�����
					if (priority(i)!=INF&&augmenting_path(i, j)) {//�ѷ���,���ҿ�����
#if 0
						//��ӡ���е�priority:
						for (int i = 0; i < n; i++)
							std::cout << "p" << i << " is " << priority(i) << ",";
						std::cout << std::endl;
#endif
						if (forward_augmenting_path(i, j)) {//�����
							if (priority(j) > priority(i) + cost(i, j)) {//���ÿɸ��µĸ���
								priority(j) = priority(i) + cost(i, j);
								parent(j) = i;
								update = true;
							}
						}
						else {//�����
							if (priority(j) > priority(i) - cost(j, i)) {//���ÿɸ��µĸ���
								priority(j) = priority(i) - cost(j, i);
								parent(j) = i;
								update = true;
							}
						}
					}
				}
			
			if (times == n - 1)//���ڸ���
				return -1;
			times++;
		}
		//Bellman-Ford�㷨�Ѿ��ҵ��������ٵ�����·
		if (parent(f) == -1)//����flow����ʣ��ʱ��û������·��,����-1
			return -1;

		int fl = flow; int temp = f;
#ifdef _DEBUG
		Stack<int> sk;
#endif
		//���������ڵ���С����·��
		while (temp != s) {
			fl = std::min(fl, augmenting_path(parent(temp), temp));//�������·����Ҫͨ��������
#ifdef _DEBUG
			sk.push(parent(temp));
#endif
			temp = parent(temp);
		}
		flow -= fl;
		cos += fl * priority(f);//�ۼƷ���,����������·Ҳ�᷵�����߷���·��Ǯ
		temp = f;
		while (temp != s) {//�ٴα�������·��,���µ㡢���ϵ�������Ϣ
			if (forward_augmenting_path(parent(temp), temp)) {//��������·��
				vertex(temp) += fl;
				edge(parent(temp), temp) += fl;
			}
			else //��������·��
				edge(temp, parent(temp)) -= fl;
			temp = parent(temp);
		}
#ifdef _DEBUG
		//��ӡ������Ϣ
		std::cout << "The path is:";
		while (!sk.empty())
			std::cout << sk.pop() << "->";
		std::cout << f << ",and flow is " << fl << ",unit-price of flow is " << priority(f) << std::endl;
#endif
	}
	return cos;
}