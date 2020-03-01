#pragma once

#include "Graph.h"
#include "Vector.h"

#define INT_MAX 2147483647

template<typename Tv>
class Vertex {
public:
	Tv data;
	int inDegree;//���
	int outDegree;//����
	VStatus status;//״̬
	int dTime, fTime;//ʱ���ǩ
	int parent;//���ڵ�
	int priority;//�ڱ������е����ȼ�(���ͨ·�����̿�ߵ�)

	Vertex(Tv const &d = (Tv) 0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template<typename Te>
class Edge {
public:
	Te data;//����
	int weight;//Ȩ��(���ߴ���������)
	int cost;//����
	EType type;//����
	Edge(Te const &d, int w) ://�����±�
		data(d), weight(w), type(UNDETERMINED) {}
	Edge(Te const &d,int w,int c)://������С�����õı�
		data(d),weight(w),type(UNDETERMINED),cost(c){}
};

template<typename Tv,typename Te>
class GraphMartrix : public Graph<Tv, Te>{//���ڽӾ���ʵ�ֵ�ͼ
private:
	Vector<Vertex<Tv> > V;//���㼯
	Vector<Vector<Edge<Te>* > >E;//�߼�
public:
	GraphMartrix() { this->n = this->e = 0; };
	~GraphMartrix() {
		for (int j = 0; j < this->n; j++)
			for (int k = 0; k < this->n; k++) {
				delete E[j][k];
			}
	}

	virtual Tv& vertex(int i) { return V[i].data; }//���ض��������
	virtual int inDegree(int i) { return V[i].inDegree; }//���
	virtual int outDegree(int i) { return V[i].outDegree; }//����
	
	virtual int firstNbr(int i) { return nextNbr(i, this->n); } //�׸��ڽӶ���
	virtual int nextNbr(int i, int j) //����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
		{ while ((-1 < j) && (!exists(i, --j))); return j; } //����������̽
	virtual VStatus& status(int i) { return V[i].status; } //״̬
	virtual int& dTime(int i) { return V[i].dTime; } //ʱ���ǩdTime
	virtual int& fTime(int i) { return V[i].fTime; } //ʱ���ǩfTime
	virtual int& parent(int i) { return V[i].parent; } //�ڱ������еĸ���
	virtual int& priority(int i) { return V[i].priority; } //�ڱ������е����ȼ���

	// ����Ķ�̬����
	virtual int insert(Tv const& vertex) { //���붥�㣬���ر��
		for (int j = 0; j < this->n; j++) 
			E[j].insert(nullptr); 
		this->n++; //������Ԥ��һ��Ǳ�ڵĹ�����
		E.insert(Vector<Edge<Te>* >(nullptr,0, this->n)); //�����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex)); //������������һ������
	}
	virtual Tv remove(int i) { //ɾ����i�����㼰������ߣ�0 <= i < n��
		for (int j = 0; j < this->n; j++) //���г���
		       if (exists(i, j)) 
			   { delete E[i][j]; V[j].inDegree--; } //����ɾ��
		E.remove(i); this->n--; //ɾ����i��
		Tv vBak = vertex(i); V.remove(i); //ɾ������i
		for (int j = 0; j < this->n; j++) //�������
		       if (Edge<Te> * e = E[j].remove(i)) { 
				   delete e; 
				   V[j].outDegree--; 
			   } //����ɾ��
		return vBak; //���ر�ɾ���������Ϣ
	}

	// �ߵ�ȷ�ϲ���
	virtual bool exists(int i, int j) //��(i, j)�Ƿ����
		{ return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr; }
	// �ߵĻ�����������ѯ����i��j֮������ߣ�0 <= i, j < n��exists(i, j)��
	virtual EType & type(int i, int j) { return E[i][j]->type; } //��(i, j)������
	virtual Te& edge(int i, int j) { return E[i][j]->data; } //��(i, j)������
	virtual int& weight(int i, int j) { return E[i][j]->weight; } //��(i, j)��Ȩ��
	virtual int& cost(int i, int j) { return E[i][j]->cost; }//��(i,j)��cost
	// �ߵĶ�̬����
	virtual void insert(Te const& edge, int w, int i, int j) { //����Ȩ��Ϊw�ı�e = (i, j)
		if (exists(i, j)) return; //ȷ���ñ��в�����
		E[i][j] = new Edge<Te>(edge, w); //�����±�
		this->e++; V[i].outDegree++; V[j].inDegree++; //���±߼������������Ķ���
	}
	virtual Te remove(int i, int j) { //ɾ������i��j֮������ߣ�exists(i, j)��
	    Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; //���ݺ�ɾ���߼�¼
		this->e--; V[i].outDegree--; V[j].inDegree--; //���±߼������������Ķ���
	    return eBak; //���ر�ɾ���ߵ���Ϣ
	}
	//������
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