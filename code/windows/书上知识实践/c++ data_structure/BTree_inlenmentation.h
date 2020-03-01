#pragma once

#include "BTree.h"

template<typename T>
BTNode<T>* BTree<T>::search(const T&e) {//����
	BTNode<T>* v = _root;
	_hot = nullptr;
	while (v) {
		int r = v->key.search(e);//Vector�Ĳ���,�Ӻ���ǰ��,���ɹ����ض�Ӧ����,ʧ�ܷ���
		if (0 <= r && e == v->key[r])
			return v;
		_hot = v; v = v->child[r + 1];//�����ҵ���r��ָ��ֵһ����eС,����eҪ�ھ���r��ָ�ڵ���Һ��ӽڵ���,��v->child[r+1]
	}
	return nullptr;
}

template<typename T>
bool BTree<T>::insert(const T&e) { //����
	BTNode<T>* v = search(e);
	if (v)//�ҵ�,˵������
		return false;
	int r = _hot->key.search(e);
	_hot->key.insert(r+1, e);
	_hot->child.insert(r + 2,nullptr);
	_size++;
	solveOverflow(_hot);
	return true;
}

template<typename T>
bool BTree<T>::remove(const T&e) {//ɾ��
	BTNode<T>* v = search(e);
	if (!v)//���û�ҵ�,ֱ�ӷ���
		return false;
	int r = v->key.search(e);
	if (v->child[0]) {//���v����Ҷ�ڵ�,��ָ����ӽڵ㲻��nullptr,�����ӽڵ�,��ʱͨ������ʹv��ΪҶ�ڵ�
		BTNode<T>* u = v->child[r + 1];
		while (u->child[0])u = u->child[0];//�ҵ�e��ֱ�Ӻ�̶�Ӧ�Ľڵ�
		v->key[r] = u->key[0]; v = u; r = 0;//������ֵ��,��v��r����Ϊ���ҵ������
	}
	v->key.remove(r);
	v->child.remove(r + 1);//ע:v��ʱ�Ѿ���Ҷ�ڵ���,��ʵɾ�ĸ���һ��,����remove[0]Ҳ����
	_size--;
	solveUnderflow(v);
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNode<T> * v) {//���������������ķ��Ѳ���
	while (true){//�Ӵ����,�Ӵ�������,���ֳ�һ���ڵ㵽������,��ʹ����Ҳ�п������,������Ҫ���ϼ��
		if (v->key.size() < _order)//�������,���˳�,_order=4,��˳����ڵ�������3��С�ڵ�,4���ӽڵ�
			break;
		int r = v->key.size() / 2;
		BTNode<T>* u = new BTNode<T>();
		//��v����r���key�Ͷ�Ӧchild��������u�в�ɾ��
		u->key.copy(v->key, r + 1, v->key.size());
		v->key.remove(r + 1, v->key.size());
		u->child.copy(v->child, r + 2, v->child.size());
		v->child.remove(r + 2, v->child.size());
		u->child.insert(0,v->child.remove(r + 1));//��v���һ�����뵽u�Ŀ�ͷ,����u��Ϊ��һ�������ĳ����ڵ�

		//��u���ص��ӽڵ�ĸ���ȫ���ĳ�u
		if (u->child[0])
			for (int i = 0; i < u->child.size(); i++)
				u->child[i]->parent = u;
		BTNode<T>* p = v->parent;
		if (!p) {//���pΪ��,����v�Ǹ��ڵ�,���½�һ�����ڵ�
			p = _root = new BTNode<T>();
			p->child[0] = v;//���p���´�����,��Ҫ��p��Ϊ���ĺ���,�������Ѵ���,��v�ض��Ѿ���p�ĺ�������
			v->parent = p;
		}
		int r2 = p->key.search(v->key[0]);//�϶������ҵ�
		p->key.insert(r2 + 1, v->key.remove(r));
		p->child.insert(r2 + 2, u);
		u->parent = p;
		v = p;//��ʼѭ����������Ƿ����
	}
	return;
}

template<typename T>
void BTree<T>::solveUnderflow(BTNode<T> * v) { //ɾ��������������ĺϲ�����
	while (true) {
		if (v->child.size() >= (_order + 1) / 2)//δ���,����
			break;
		BTNode<T>* p = v->parent;
		if (!p) {//v�Ѿ������ڵ���,���Ҹ��ڵ�Ҳ������
			if (!v->key.size() && v->child[0]) {//��v��key�Ѿ�ȫ������,��v���зǿպ���
				//(ע:ֻ����һ��,��Ϊ֮ǰ���׽��ʱ��,�ʹ����ӽڵ��Լ��費������,�ụ��ϲ�)
				_root = v->child[0];
				_root->parent = nullptr;
				v->child[0] = nullptr;
				release(v);
			}
			break;
		}
		int r = 0; while (p->child[r] != v)r++;//����:Ϊʲôint r = p->child.search(v)���У�����������
		//����ɾ����ʱ����ֱ��ɾ���,�������������ʱ���������ֵܽ�
		if (r > 0) {//��v����p�ĵ�һ������
			BTNode<T>* ls = p->child[r - 1];
			if (ls->child.size() > (_order + 1) / 2) {//����Ҳ��������,�ͽ�
				v->key.insert(0,p->key[r-1]);
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
				if (v->child[0])//�о�����ж��Ƕ���İ�
					v->child[0]->parent = v;
				break;
			}
		}
		//��ڵ�û�ý�,���ҽڵ��
		if (p->child.size() - 1 > r) {//���ҽڵ�
			BTNode<T>* rs = p->child[r + 1];
			if (rs->child.size() > (_order + 1) / 2) {//���ֵ��������Ҳ��������ͽ�
				v->key.insert(v->key.size(), p->key[r]);
				v->child.insert(v->child.size(), rs->child.remove(0));
				p->key[r] = rs->key.remove(0);
				if (v->child[v->child.size() - 1])
					v->child[v->child.size() - 1]->parent = v;
				break;
			}
		}
		//���Ҷ�ҪôΪ��,Ҫô��̫��,��ϲ�,�����׽�һ��,��ʱ���ܻᷢ�����ڵ�Ҳ����,��Ҫ�ٴμ��
		//ע:�����ܺϲ�������,��Ϊ�����ֵ�����Ҳ����[m/2]��,�Լ�����Ҳ��[m/2]-1��
		if (0 < r) {//�������ֵ�,��ϲ������ֵ���,�����Լ���key����,����ѡ���ƶ��Լ�
			BTNode<T>* ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1));//��p�е�key��ls,��ʱls��key��child�ȳ�
			p->child.remove(r);//��v��p��ɾ��
			ls->child.insert(ls->child.size(), v->child.remove(0));//�Ȱ�v��ĵ�һ��child�ƹ�ȥ,��v��key��child�ȳ�,����֮���ƶ�
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
			while (!v->key.empty()) {//��v��ת��ls��
				ls->key.insert(ls->key.size(), v->key.remove(0));
				ls->child.insert(ls->child.size(), v->child.remove(0));
				if (ls->child[ls->child.size() - 1])//����ӽڵ����,������ָ��ls
					ls->child[ls->child.size() - 1]->parent = ls;
			}
			release(v);
		}
		else {//�ϲ������ֵ���,�����Լ���key����,���ƶ��Լ�
			BTNode<T>* rs = p->child[r + 1];
			rs->key.insert(0, p->key.remove(r));
			p->child.remove(r);//��v��p��ɾ��
			rs->child.insert(0, v->child.remove(v->child.size() - 1));//����һ����ȥ
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
		v = p;//�������
	}

	return;
}