#include "GraphMatrix.h"

int main6() {
	//����Floyd���нڵ�����·���㷨
	std::cout << "����Floyd���нڵ�����·���㷨" << std::endl;
	GraphMartrix<int, int> g;
	//�������㷨����P402��ͼ
	for (int i = 0; i < 5; i++)
		g.insert(i);
	g.logVec();
	g.insert(0, 3, 0, 1);
	g.insert(0, 8, 0, 2);
	g.insert(0, -4, 0, 4);
	g.insert(0, 1, 1, 3);
	g.insert(0, 7, 1, 4);
	g.insert(0, 4, 2, 1);
	g.insert(0, 2, 3, 0);
	g.insert(0, -5, 3, 2);
	g.insert(0, 6, 4, 3);
	g.logVec();
	//����Floyd�㷨
	Floyd<int>* arr = new Floyd<int>[5 * 5];
	g.Floyd_Warshall(arr);

	//���������������㷨TSP(traveling salesman problem),ͼΪ��ս������ƾ���P191��ʾ
	std::cout << "���������������㷨TSP(traveling salesman problem)" << std::endl;
	GraphMartrix<int, int> t;
	for (int i = 0; i < 5; i++)
		t.insert(i);
	t.insert(0, 3, 0, 1);
	t.insert(0, 4, 0, 3);
	t.insert(0, 5, 1, 2);
	t.insert(0, 4, 2, 0);
	t.insert(0, 5, 2, 3);
	t.insert(0, 3, 3, 4);
	t.insert(0, 6, 4, 1);
	t.insert(0, 7, 4, 0);

	std::cout << "The tsp cost is " << t.tsp(0) << std::endl;
	
	//�������������Ford-Fulkson�㷨,ͼΪ��ս������ƾ���P209
	std::cout << "����Ford-Fulkson������㷨(dsp)" << std::endl;
	GraphMartrix<int, int> f;
	for (int i = 0; i < 5; i++)
		f.insert(i);
	f.insert(0, 10, 0, 1);
	f.insert(0, 2, 0, 2);
	f.insert(0, 6, 1, 2);
	f.insert(0, 6, 1, 3);
	f.insert(0, 5, 2, 4);
	f.insert(0, 3, 3, 2);
	f.insert(0, 8, 3, 4);

	std::cout << "The max flow is " <<  f.Ford_Fulkerson(0,4) << std::endl;

	//����Edmonds-Karps�㷨,ͼ��Ϊ�����Ǹ�
	std::cout << "����Edmonds-Karps������㷨(bfs)" << std::endl;
	std::cout << "The max flow is " << f.Edmonds_Karps(0, 4) << std::endl;

	//������Bellman-Ford�㷨Ѱ�һ�������·������С�������㷨,ͼ����ս������ƾ���P222,����ͼ�����޸ļ���
	std::cout << "������С�������㷨(��Bellman-Ford�㷨Ѱ����С����·��)" << std::endl;
	f.cost(0, 1) = 2;
	f.cost(0, 2) = 4;
	f.cost(1, 2) = 6;
	f.cost(1, 3) = 2;
	f.cost(2, 4) = 2;
	f.cost(3, 2) = 3;
	f.cost(3, 4) = 6;
	int n = f.min_cost_flow(0, 4, 9);
	std::cout << "The total cost is " << n << std::endl;
	

	return 0;
}