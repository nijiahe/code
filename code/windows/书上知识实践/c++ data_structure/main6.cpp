#include "GraphMatrix.h"

int main6() {
	//测试Floyd所有节点对最短路径算法
	std::cout << "测试Floyd所有节点对最短路径算法" << std::endl;
	GraphMartrix<int, int> g;
	//插入如算法导论P402的图
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
	//测试Floyd算法
	Floyd<int>* arr = new Floyd<int>[5 * 5];
	g.Floyd_Warshall(arr);

	//测试旅行商问题算法TSP(traveling salesman problem),图为挑战程序设计竞赛P191所示
	std::cout << "测试旅行商问题算法TSP(traveling salesman problem)" << std::endl;
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
	
	//测试最大流问题Ford-Fulkson算法,图为挑战程序设计竞赛P209
	std::cout << "测试Ford-Fulkson最大流算法(dsp)" << std::endl;
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

	//测试Edmonds-Karps算法,图仍为如上那个
	std::cout << "测试Edmonds-Karps最大流算法(bfs)" << std::endl;
	std::cout << "The max flow is " << f.Edmonds_Karps(0, 4) << std::endl;

	//测试用Bellman-Ford算法寻找花费最少路径的最小费用流算法,图是挑战程序设计竞赛P222,对上图进行修改即可
	std::cout << "测试最小费用流算法(用Bellman-Ford算法寻找最小化非路径)" << std::endl;
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