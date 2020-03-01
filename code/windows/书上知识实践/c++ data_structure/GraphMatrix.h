#pragma once

#include "Graph.h"
#include "Vector.h"

#define INT_MAX 2147483647

template<typename Tv>
class Vertex {
public:
	Tv data;
	int inDegree;//入度
	int outDegree;//出度
	VStatus status;//状态
	int dTime, fTime;//时间标签
	int parent;//父节点
	int priority;//在遍历树中的优先级(最短通路、极短跨边等)

	Vertex(Tv const &d = (Tv) 0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template<typename Te>
class Edge {
public:
	Te data;//数据
	int weight;//权重(或者存放最大流量)
	int cost;//花费
	EType type;//类型
	Edge(Te const &d, int w) ://构造新边
		data(d), weight(w), type(UNDETERMINED) {}
	Edge(Te const &d,int w,int c)://构造最小费用用的边
		data(d),weight(w),type(UNDETERMINED),cost(c){}
};

template<typename Tv,typename Te>
class GraphMartrix : public Graph<Tv, Te>{//以邻接矩阵实现的图
private:
	Vector<Vertex<Tv> > V;//顶点集
	Vector<Vector<Edge<Te>* > >E;//边集
public:
	GraphMartrix() { this->n = this->e = 0; };
	~GraphMartrix() {
		for (int j = 0; j < this->n; j++)
			for (int k = 0; k < this->n; k++) {
				delete E[j][k];
			}
	}

	virtual Tv& vertex(int i) { return V[i].data; }//返回顶点的数据
	virtual int inDegree(int i) { return V[i].inDegree; }//入度
	virtual int outDegree(int i) { return V[i].outDegree; }//出度
	
	virtual int firstNbr(int i) { return nextNbr(i, this->n); } //首个邻接顶点
	virtual int nextNbr(int i, int j) //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
		{ while ((-1 < j) && (!exists(i, --j))); return j; } //逆向线性试探
	virtual VStatus& status(int i) { return V[i].status; } //状态
	virtual int& dTime(int i) { return V[i].dTime; } //时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; } //时间标签fTime
	virtual int& parent(int i) { return V[i].parent; } //在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; } //在遍历树中的优先级数

	// 顶点的动态操作
	virtual int insert(Tv const& vertex) { //插入顶点，返回编号
		for (int j = 0; j < this->n; j++) 
			E[j].insert(nullptr); 
		this->n++; //各顶点预留一条潜在的关联边
		E.insert(Vector<Edge<Te>* >(nullptr,0, this->n)); //创建新顶点对应的边向量
		return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
	}
	virtual Tv remove(int i) { //删除第i个顶点及其关联边（0 <= i < n）
		for (int j = 0; j < this->n; j++) //所有出边
		       if (exists(i, j)) 
			   { delete E[i][j]; V[j].inDegree--; } //逐条删除
		E.remove(i); this->n--; //删除第i行
		Tv vBak = vertex(i); V.remove(i); //删除顶点i
		for (int j = 0; j < this->n; j++) //所有入边
		       if (Edge<Te> * e = E[j].remove(i)) { 
				   delete e; 
				   V[j].outDegree--; 
			   } //逐条删除
		return vBak; //返回被删除顶点的信息
	}

	// 边的确认操作
	virtual bool exists(int i, int j) //边(i, j)是否存在
		{ return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr; }
	// 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
	virtual EType & type(int i, int j) { return E[i][j]->type; } //边(i, j)的类型
	virtual Te& edge(int i, int j) { return E[i][j]->data; } //边(i, j)的数据
	virtual int& weight(int i, int j) { return E[i][j]->weight; } //边(i, j)的权重
	virtual int& cost(int i, int j) { return E[i][j]->cost; }//边(i,j)的cost
	// 边的动态操作
	virtual void insert(Te const& edge, int w, int i, int j) { //插入权重为w的边e = (i, j)
		if (exists(i, j)) return; //确保该边尚不存在
		E[i][j] = new Edge<Te>(edge, w); //创建新边
		this->e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点的度数
	}
	virtual Te remove(int i, int j) { //删除顶点i和j之间的联边（exists(i, j)）
	    Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; //备份后删除边记录
		this->e--; V[i].outDegree--; V[j].inDegree--; //更新边计数与关联顶点的度数
	    return eBak; //返回被删除边的信息
	}
	//调试用
	void logVec() {
		std::cout << "Vertex size is " << V.size() << std::endl;
		for (int i = 0; i < this->n; i++) {
			std::cout << "Edge from " << i << " size is" << E[i].size() << std::endl;
			for (int j = 0; j < this->n; j++) {
				if (exists(i, j))
					std::cout << i << " to " << j << " weight " << weight(i, j) << std::endl;
			}
		}
		std::cout << std::endl;

	}
};