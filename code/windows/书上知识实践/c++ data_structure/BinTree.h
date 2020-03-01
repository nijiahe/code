#pragma once

#include "BinNode.h"

template<typename T>class BinTree {
public:
	BinTree() : _size(0), _root(NULL) { } //构造函数
	~BinTree() { if (0 < _size) this->remove(_root); } //析构函数
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNode<T>* root() const { return _root; }
	BinNode<T>* insertAsRoot(T const& e); //插入根节点
	BinNode<T>* insertAsLC(T const &e, BinNode<T> *x);
	BinNode<T>* insertAsRC(T const &e, BinNode<T> *x);
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &T); //T作为x左子树接入
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &T); //T作为x右子树接入
	int remove(BinNode<T>* x); //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNode<T>* x); //将子树x从当前树中摘除，并将其转换为一棵独立子树
	
	template <typename VST> //操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //层次遍历
	template < typename VST> //操作器
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //先序遍历
	template < typename VST> //操作器
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //中序遍历
	template < typename VST> //操作器
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //后序遍历

	/*bool operator< (BinTree<T> const& t) //比较器（其余自行补充）
		{ return _root && t._root && lt(_root, t._root); }
	bool operator== (BinTree<T> const& t) //判等器
		{ return _root && t._root && (_root == t._root); }*/
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);//update node_x's height
	void updateHeightAbove(BinNode<T>* x);//update all the ancestry's and node_x's height
	
};

#include "BinTree_inplenmentation.h"