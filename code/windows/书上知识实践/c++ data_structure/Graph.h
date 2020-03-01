#pragma once

#include "Stack.h"

#define INF INT_MAX

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //���ڱ�����������������

template<typename Te>
struct Floyd {
	Te cost;//���·��Ȩ��
	int path;//ǰ��
};

template < typename Tv, typename Te> //�������͡�������
class Graph { //ͼGraphģ����
private:
	void reset() { //���ж��㡢�ߵĸ�����Ϣ��λ
		for (int i = 0; i < n; i++) { //���ж����       
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; //״̬��ʱ���ǩ
			parent(i) = -1; priority(i) = INF; //���ڱ������еģ����ڵ㣬���ȼ���
			for (int j = 0; j < n; j++) //���бߵ�
			if (exists(i, j)) type(i, j) = UNDETERMINED; //����
		}
	}
	void BFS(int v, int& clock); //(��ͨ��)������������㷨,Breadth First Search
	void DFS(int v, int& clock); //(��ͨ��)������������㷨,Depth First Search
	void BCC(int v, int& clock, Stack<int>& S); //(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨,bi-connected component
	bool TSort(int v, int& clock, Stack<Tv>* S); //(��ͨ��)����DFS�����������㷨,topology sort
	template <typename PU> void PFS(int s, PU prioUpdater); //(��ͨ��)���ȼ��������,priority first search
public:
	// ����
	int n; //��������
	virtual int insert(Tv const&) = 0; //���붥�㣬���ر��
	virtual Tv remove(int) = 0; //ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(int) = 0; //����v������(�ö����ȷ����)
	virtual int inDegree(int) = 0; //����v�����(�ö����ȷ����)
	virtual int outDegree(int) = 0; //����v�ĳ���(�ö����ȷ����)
	virtual int firstNbr(int v) = 0; //����v���׸��ڽӶ���
	virtual int nextNbr(int v, int u) = 0; //����v��(����ڶ���j��)��һ�ڽӶ���
	virtual VStatus& status(int v) = 0; //����v��״̬
	virtual int& dTime(int) = 0; //����v��ʱ���ǩdTime
	virtual int& fTime(int) = 0; //����v��ʱ���ǩfTime
	virtual int& parent(int) = 0; //����v�ڱ������еĸ���
	virtual int& priority(int) = 0; //����v�ڱ������е����ȼ���

	// �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e; //������
	virtual bool exists(int, int) = 0; //��(v, u)�Ƿ����
	virtual void insert(Te const& edge, int w, int i, int j) = 0; //�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0; //ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType & type(int i, int j) = 0; //��(i, j)������
	virtual Te& edge(int i, int j) = 0; //��(i, j)������(�ñߵ�ȷ����)
	virtual int& cost(int i, int j) = 0;//���ر�(i,j)��cost
	virtual int& weight(int i, int j) = 0; //��(i, j)��Ȩ��

	// �㷨
	void bfs(int s); //������������㷨
	void dfs(int s); //������������㷨
	void bcc(int s); //����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int s); //����DFS�����������㷨

	void prim(int s); //(��С������)��С֧����Prim�㷨,ͨ����ÿ�������ɳ�
	void kruskal();//��С������Kruskal�㷨,ͨ��̰���㷨,ÿ����С��ȡδ�����ֵ�����ı�,������ʵ����,�����Ӷ���O(ElgE)

	bool bellman_ford(int s);//Bellman-Ford��Դ���·���㷨,�������бߴ����и���Ȩ��,���������һ��������·,�򷵻�false��֪�޽�
	void dijkstra(int s); //(��Դ���·��)���·��Dijkstra�㷨

	template <typename PU> void pfs(int s, PU prioUpdater); //���ȼ��������

	//���нڵ�����·���㷨
	Te* slow_all_pair_shortest_paths(Te* twoD_arr);//ͨ����������ʾ���нڵ�Ե����·��,����n*n�ľ���,�������и�����ͼ,O(n^4)
	Floyd<Te>* Floyd_Warshall(Floyd<Te>* twoD_arr);//�����������нڵ�����·���㷨,O(n^3)
	void log_FloudMartrix(Floyd<Te>* arr,int k);//����n*n����,�͵�ǰ��kֵ

	//����������,ÿ���ڵ���һ�ε����·��(���·��Ӧ��Ҳ�������������,��״̬ѹ��DP)
	int tsp(int v);//����������(traveling salesman problem),����S�ص�S,����ÿ����ֻ����һ��,�����·����ͼ�㷨,�������Ϊ��ʼ��
	int _TSP(int *dp,int S, int v, int E);//�����������ڲ��ú���,�������Ϊdp����(��¼��ǰ���ϵ�ǰ�������,�ص�E�����·��)

	//���������,Ĭ���޻�ͼ
	//Ford-Fulkerson��dspѰ������·���㷨,O(fE)
	Tv augmenting_path(int from, int to);//�ж�����·�ܷ�����,����������,����0,���򷵻�����·�����������
	bool forward_augmenting_path(int from, int to);//�ж�һ��������·������������㻹�����������
	Tv Ford_Fulkerson(int s,int f);//Ford-Fulkerson������㷨,��ʵFord-Fulkersonû��˵��Ѱ������·�����㷨,��Ĭ�ϴ��㷨��ͨ�������������Ѱ�ҵ�,O(fE),����һ�������������1ʱ,�������������߻ᵼ����������ﵽO(f)
	Tv Ford_Fulkerson_dsp(int v,int f,int flow);//Ford_Fulkerson�õ�������������㷨,���뵱ǰ��,�յ�,���ش˴�·���ϵ���
	//Edmonds-Karps��bfsѰ������·���㷨,O(V*E^2)
	Tv Edmonds_Karps(int s, int f);//Edmonds Karps�㷨,ͨ��bfsѰ������·��,����ÿһ�������u->v��Ϊ�ؼ��ߺ�,����·������+2�����ٴγ�Ϊ�ؼ���,·�������޷�����V-1,ÿ������·���ض�����һ�������,�����ǹ������,·�����Ȳ����ܱ�С,��������·��=�ؼ�������������E*(V-1)/2,ÿ��bfsO(V+E),���Ը��Ӷ�ΪO(V*E^2)
	Tv Edmonds_Karps_bfs(int v, int f, int flow);
	//Dinic�㷨,ͨ��bfs��ȷ���ֲ�,Ȼ����dfs��ֻ����bfsȷ���Ĳ������ķ���Ѱ������·��,ÿ�δ˷ֲ�ṹû��·���ܵ�ʱ,�����·ֲ�,ֱ��bfs�����ҵ�ͨ��f��·��ʱ
	//......����Ĳ�ʵ����,��ս������ƾ���P217
	//��С����������
	int min_cost_flow(int s, int f, int flow);//��С����������,�˴���Bellman-Ford���㷨,����ÿ������flow-1,ÿ��Bellman-ford�㷨ʱ��O(VE),�����ܹ�O(fVE)

};

template<typename Tv, typename Te>
struct PrimPU{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {//ͼ,���ĵ�,�ھ�
		if (UNDISCOVERED == g->status(v))
			if (g->priority(uk) > g->weight(uk,v)) {
				g->priority(uk) = g->weight(uk,v);
				g->parent(v) = uk;
			}
	}
};

template<typename Tv, typename Te>
struct DijkstraPU {
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {//ͼ,���ĵ�,�ھ�
		if (UNDISCOVERED == g->status(v))
			if (g->priority(v) > g->weight(uk, v)+g->priority(uk)) {//����ھӵ����ȼ���ֵ����Ĺ���
				g->priority(v) = g->weight(uk, v) + g->priority(uk);//������ĳ�������
				g->parent(v) = uk;
			}
	}
};

//�����INFʱ�����������
int add(int a, int b) {
	if (a == INF || b == INF)
		return INF;
	return a + b;
}

#include "Graph_inplenmentation.h"