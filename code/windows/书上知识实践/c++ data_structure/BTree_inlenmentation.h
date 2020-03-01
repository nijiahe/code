#pragma once

#include "BTree.h"

template<typename T>
BTNode<T>* BTree<T>::search(const T&e) {//查找
	BTNode<T>* v = _root;
	_hot = nullptr;
	while (v) {
		int r = v->key.search(e);//Vector的查找,从后往前找,若成功返回对应的秩,失败返回
		if (0 <= r && e == v->key[r])
			return v;
		_hot = v; v = v->child[r + 1];//由于找到的r所指数值一定比e小,所以e要在就在r所指节点的右孩子节点中,即v->child[r+1]
	}
	return nullptr;
}

template<typename T>
bool BTree<T>::insert(const T&e) { //插入
	BTNode<T>* v = search(e);
	if (v)//找到,说明已有
		return false;
	int r = _hot->key.search(e);
	_hot->key.insert(r+1, e);
	_hot->child.insert(r + 2,nullptr);
	_size++;
	solveOverflow(_hot);
	return true;
}

template<typename T>
bool BTree<T>::remove(const T&e) {//删除
	BTNode<T>* v = search(e);
	if (!v)//如果没找到,直接返回
		return false;
	int r = v->key.search(e);
	if (v->child[0]) {//如果v不是叶节点,即指向的子节点不是nullptr,即有子节点,此时通过交换使v变为叶节点
		BTNode<T>* u = v->child[r + 1];
		while (u->child[0])u = u->child[0];//找到e的直接后继对应的节点
		v->key[r] = u->key[0]; v = u; r = 0;//交换数值后,将v和r记载为新找到的这个
	}
	v->key.remove(r);
	v->child.remove(r + 1);//注:v此时已经是叶节点了,其实删哪个都一样,不妨remove[0]也可以
	_size--;
	solveUnderflow(v);
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNode<T> * v) {//插入后上溢而引发的分裂操作
	while (true){//子代溢出,子代将分裂,并分出一个节点到父代中,致使父代也有可能溢出,所以需要不断检查
		if (v->key.size() < _order)//不再溢出,则退出,_order=4,则此超级节点最多包含3个小节点,4个子节点
			break;
		int r = v->key.size() / 2;
		BTNode<T>* u = new BTNode<T>();
		//将v中秩r后的key和对应child都拷贝到u中并删除
		u->key.copy(v->key, r + 1, v->key.size());
		v->key.remove(r + 1, v->key.size());
		u->child.copy(v->child, r + 2, v->child.size());
		v->child.remove(r + 2, v->child.size());
		u->child.insert(0,v->child.remove(r + 1));//将v最后一个插入到u的开头,这样u成为了一个正常的超级节点

		//将u记载的子节点的父亲全部改成u
		if (u->child[0])
			for (int i = 0; i < u->child.size(); i++)
				u->child[i]->parent = u;
		BTNode<T>* p = v->parent;
		if (!p) {//如果p为空,代表v是父节点,则新建一个根节点
			p = _root = new BTNode<T>();
			p->child[0] = v;//如果p是新创建的,需要让p成为他的孩子,否则若已存在,则v必定已经在p的孩子们中
			v->parent = p;
		}
		int r2 = p->key.search(v->key[0]);//肯定不会找到
		p->key.insert(r2 + 1, v->key.remove(r));
		p->child.insert(r2 + 2, u);
		u->parent = p;
		v = p;//开始循环上升检查是否溢出
	}
	return;
}

template<typename T>
void BTree<T>::solveUnderflow(BTNode<T> * v) { //删除后下溢而引发的合并操作
	while (true) {
		if (v->child.size() >= (_order + 1) / 2)//未溢出,返回
			break;
		BTNode<T>* p = v->parent;
		if (!p) {//v已经到根节点了,并且根节点也下溢了
			if (!v->key.size() && v->child[0]) {//若v的key已经全被借完,且v仍有非空孩子
				//(注:只会有一个,因为之前向父亲借的时候,就代表子节点自己借不出来了,会互相合并)
				_root = v->child[0];
				_root->parent = nullptr;
				v->child[0] = nullptr;
				release(v);
			}
			break;
		}
		int r = 0; while (p->child[r] != v)r++;//疑问:为什么int r = p->child.search(v)不行？？？？？？
		//由于删除的时候是直接删后继,所以这里调整的时候先向左兄弟借
		if (r > 0) {//若v不是p的第一个孩子
			BTNode<T>* ls = p->child[r - 1];
			if (ls->child.size() > (_order + 1) / 2) {//借了也不会下溢,就借
				v->key.insert(0,p->key[r-1]);
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
				if (v->child[0])//感觉这个判断是多余的吧
					v->child[0]->parent = v;
				break;
			}
		}
		//左节点没得借,问右节点借
		if (p->child.size() - 1 > r) {//有右节点
			BTNode<T>* rs = p->child[r + 1];
			if (rs->child.size() > (_order + 1) / 2) {//右兄弟如果借了也不会下溢就借
				v->key.insert(v->key.size(), p->key[r]);
				v->child.insert(v->child.size(), rs->child.remove(0));
				p->key[r] = rs->key.remove(0);
				if (v->child[v->child.size() - 1])
					v->child[v->child.size() - 1]->parent = v;
				break;
			}
		}
		//左右都要么为空,要么都太瘦,则合并,并向父亲借一个,此时可能会发生父节点也下溢,需要再次检测
		//注:不可能合并后还下溢,因为左右兄弟最少也会有[m/2]个,自己最少也有[m/2]-1个
		if (0 < r) {//存在左兄弟,则合并到左兄弟中,由于自己的key更少,所以选择移动自己
			BTNode<T>* ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1));//将p中的key给ls,此时ls的key和child等长
			p->child.remove(r);//将v从p中删掉
			ls->child.insert(ls->child.size(), v->child.remove(0));//先把v里的第一个child移过去,让v中key和child等长,方便之后移动
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
			while (!v->key.empty()) {//将v都转入ls中
				ls->key.insert(ls->key.size(), v->key.remove(0));
				ls->child.insert(ls->child.size(), v->child.remove(0));
				if (ls->child[ls->child.size() - 1])//如果子节点存在,则让其指向ls
					ls->child[ls->child.size() - 1]->parent = ls;
			}
			release(v);
		}
		else {//合并到右兄弟中,由于自己的key更少,仍移动自己
			BTNode<T>* rs = p->child[r + 1];
			rs->key.insert(0, p->key.remove(r));
			p->child.remove(r);//将v从p中删掉
			rs->child.insert(0, v->child.remove(v->child.size() - 1));//先移一个过去
			if (rs->child[0])
				rs->child[0]->parent = rs;
			while (!v->key.empty()) {
				rs->key.insert(0, v->key.remove(v->key.size() - 1));
				rs->child.insert(0, v->child.remove(v->child.size() - 1));
				if (rs->child[0])
					rs->child[0]->parent = rs;
			}
			release(v);
		}
		v = p;//继续检查
	}

	return;
}