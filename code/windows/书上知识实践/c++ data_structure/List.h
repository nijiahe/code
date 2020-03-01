#pragma once

#include "ListNode.h"

typedef int Rank;

template<typename T>
class List
{
private:
	int _size; 
	ListNode<T>* _header; 
	ListNode<T>* _trailer;

protected:
	void init(); //�б���ʱ�ĳ�ʼ��
	int clear(); //������нڵ�
	void copyNodes(ListNode<T>*, int); //��ʼ���б������б�����λ��p���n��
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int); //�鲢
	void mergeSort(ListNode<T>*&, int); //�Դ�p��ʼ������n���ڵ�鲢����
	void selectionSort(ListNode<T>*, int); //�Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(ListNode<T>*, int); //�Դ�p��ʼ������n���ڵ��������
	ListNode<T>* getNodeByRank(Rank r) const;
	void swapNode(ListNode<T>* n1, ListNode<T>* n2);//���ı�ڵ��ַ�������·���ڵ������£��������ڵ��������е�˳����ȫ����

public:
	//���캯��
	List(); //Ĭ��
	List(List<T> const& L); //���帴���б�L
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNode<T>* p, int n); //�����б�����λ��p���n��
	//��������
	~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return _size <= 0; } //�п�
	T& operator[] (Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	ListNode<T>* first() { return _header->_succ; } //�׽ڵ�λ��
	ListNode<T>* last() const { return _trailer->_pred; } //ĩ�ڵ�λ��
	bool valid(ListNode<T>* p) //�ж�λ��p�Ƿ����Ϸ�
	{ return p && (_trailer != p) && (_header != p); } //��ͷ��β�ڵ��ͬ��NULL
	ListNode<T>* find(T const& e) const //�����б����
	{ return find(e, _size, _trailer); }
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const; //����������ң��ڽڵ�p��n����ǰ�����ҵ�e�������
	ListNode<T>* search(T const& e) const //�����б����
	{ return search(e, _size, _trailer); }
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const; //�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�������e�������
	ListNode<T>* selectMax(ListNode<T>* p, int n); //��p����n-1�������ѡ�������
	ListNode<T>* selectMax() { return selectMax(_header->_succ, _size); } //���������
	//��д���ʽӿ�
	ListNode<T>* insertAsFirst(T const& e); //��e�����׽ڵ����
	ListNode<T>* insertAsLast(T const& e); //��e����ĩ�ڵ����
	ListNode<T>* insertA(ListNode<T>* p, T const& e); //��e����p�ĺ�̲��루After��
	ListNode<T>* insertB(ListNode<T>* p, T const& e); //��e����p��ǰ�����루Before��
	T remove(ListNode<T>* p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); } //ȫ�б�鲢
	void sort(ListNode<T>* p, int n); //�б��������򣬶��û����Ľӿڣ����p������ǰ������Ϊ�û�����������_header���ھ����������ڻ�ԭ
	void sort() { sort(first(), _size); } //�б���������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	void reverse(); //ǰ���ã�ϰ�⣩
	//����
	void traverse(void(*) (T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	template < typename VST> void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
};

#include "List_implementation.h"