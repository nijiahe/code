#pragma once

#include "BinNode.h"

template<typename T>class BinTree {
public:
	BinTree() : _size(0), _root(NULL) { } //���캯��
	~BinTree() { if (0 < _size) this->remove(_root); } //��������
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNode<T>* root() const { return _root; }
	BinNode<T>* insertAsRoot(T const& e); //������ڵ�
	BinNode<T>* insertAsLC(T const &e, BinNode<T> *x);
	BinNode<T>* insertAsRC(T const &e, BinNode<T> *x);
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &T); //T��Ϊx����������
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &T); //T��Ϊx����������
	int remove(BinNode<T>* x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNode<T>* x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	
	template <typename VST> //������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //��α���
	template < typename VST> //������
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������
	template < typename VST> //������
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //�������
	template < typename VST> //������
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //�������

	/*bool operator< (BinTree<T> const& t) //�Ƚ������������в��䣩
		{ return _root && t._root && lt(_root, t._root); }
	bool operator== (BinTree<T> const& t) //�е���
		{ return _root && t._root && (_root == t._root); }*/
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);//update node_x's height
	void updateHeightAbove(BinNode<T>* x);//update all the ancestry's and node_x's height
	
};

#include "BinTree_inplenmentation.h"