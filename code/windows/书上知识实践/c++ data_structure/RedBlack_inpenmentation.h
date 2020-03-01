#pragma once

#include "RedBlack.h"

template<typename T>
int RedBlack<T>::updateHeight(BinNode<T>* x) {//���½ڵ�߶�
	x->height = max(stature(x->lChild), stature(x->rChild));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNode<T>* RedBlack<T>::insert(const T&e) {
	BinNode<T>* &x = this->searchIn(e);
	if (x)//����Ѵ���,ֱ�ӷ���
		return x;
	//�������
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1);//-1�����ĸ߶�,Ĭ��Ϊ��ɫ
	this->_size++;
	solveDoubleRed(x);
	return x ? x : this->_hot->parent;//solveDoubleRed���յĲ�������,����˵x���ᱻ�Ķ���
}

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNode<T>* x){
	if (IsRoot(*x)) {//����Ѿ����ڵ�
		this->_root->color = RB_BLACK;
		this->_root->height++;
		return;
	}
	BinNode<T>* p = x->parent;
	if (IsBlack(p)) //���p�Ǻ�ɫ,��δ����˫��,��ֱ�ӷ���,��Ҳ�ͱ�֤��pΪ���ڵ�ʱ����ֱ�ӷ���,������g�����ڵ����
		return;
	//����
	BinNode<T>* g = p->parent;
	BinNode<T>* u = uncle(x);//�常�ڵ�,��g����p�ĺ��ӽڵ�
	if (IsBlack(u)) {//����常�ڵ��Ǻ�,��û�м����շ�˫��Ŀ���,�˴��������ֱ�ӷ���
		if (IsLChild(*x) == IsLChild(*p)) //���x��pͬ��
			p->color = RB_BLACK;//��p����ɫ��Ϊ��ɫ
		else//���
			x->color = RB_BLACK;
		g->color = RB_RED;//�������,g����ɫ�����ɺ�ɫ
		BinNode<T>* gg = g->parent;//���游
		BinNode<T>* r = FromParentTo(*g) = this->rotateAt(x);//rotate�е���3+4�ع�,�����д���������,����gg����Ӧ���Ӹ���
		r->parent = gg;//r�ĸ��ڵ����
	}
	else {//�常�Ǻ�ɫ
		p->color = RB_BLACK; p->height++;//�����height++û����,ΪʲôҪ++?,���²��Ǻ�ڵ���
		u->color = RB_BLACK; u->height++;//�����height++Ҳ��
		if (!IsRoot(*g))g->color = RB_RED;
		solveDoubleRed(g);
	}
}

template<typename T>
bool RedBlack<T>::remove(const T& e) {
	BinNode<T>* &x = this->searchIn(e);
	if (!x)//���������,����ʧ��
		return false;
	BinNode<T>* r = removeAt(x, this->_hot);//��ֱ�Ӻ�̽�����ֵ�ϵĽ���,Ȼ��ɾ��ֱ�Ӻ�����ڵ�,�����µ��ڱ�ɾλ���ϵĽڵ�
	if (!(--this->_size))//��������ڵ㶼��ɾ����,ֱ�ӷ���
		return true;
	if (!this->_hot) {//���_hotΪ��,��xΪ���ڵ�,�����Ϊ�ڽڵ�
		this->_root->color = RB_BLACK;
		updateHeight(this->_root);
		return true;
	}
	if (BlackHeightUpdated(*this->_hot))//���ʵ�ʱ�ɾ�ڵ�Ϊ��,�丸�ڵ��Ϊ��,���ƽ��
		return true;
	//����ƽ��,���½ڵ�Ϊ��,��ԭ�ȱ�ɾ�ڵ��Ϊ��,����Ϊ���,������ڵ�Ⱦ�ڼ���,���������ɫ����û�仯һ��
	if (IsRed(r)) {
		r->color = RB_BLACK; r->height++; return true;
	}
	//����,������ɾ�ڵ����������λ���ϵĽڵ㶼�Ǻ�ɫ��,����һ������һ����,��Ҫ����
	solveDoubleBlack(r);
	return true;
}

//����r�ڵ��ǽ����˱�ɾ�ڵ�λ�õ��½ڵ�,�����������Ǻ�,ɾ��һ���Ժ����˴�ͨ·�Ϻ�ɫʧ��
//���,���ڱ�ɾ�ڵ���ֱ�Ӻ��,���Խ�������r�ڵ�Ҳû�����ӽڵ�
template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNode<T>* r) {
	BinNode<T>* p = r ? r->parent : this->_hot;
	if (!p)//rΪ���ڵ�,�򷵻�
		return;
	BinNode<T>* s = (r == p->lChild) ? p->rChild : p->lChild;//r���ֵܽڵ�
	if (IsBlack(s)) {//�ֵ�sΪ��
		BinNode<T>* t = nullptr;
		if (IsRed(s->rChild))
			t = s->rChild;
		if (IsRed(s->lChild))
			t = s->lChild;
		if (t) {//���s�к�ɫ�ĺ���,�򽫺�ɫ����Ⱦ��,Ȼ�����3+4�ع�����
			RBColor oldColor = p->color;//����ԭp�ڵ����ɫ
			BinNode<T>* b = FromParentTo(*p) = this->rotateAt(t);//3+4�ع�
			if (HasLChild(*b)) {
				b->lChild->color = RB_BLACK;
				updateHeight(b->lChild);
			}
			if (HasRChild(*b)) {
				b->rChild->color = RB_BLACK;
				updateHeight(b->rChild);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else {//s�޺캢��,��s��Ϊ��
			s->color = RB_RED;
			s->height--;
			if (IsRed(p)) {//���pΪ��,BB-2R,��ʱ��ɫ����������ʧ��,����
				p->color = RB_BLACK;
			}
			else {//BB-2B,�������ϼ���Ƿ�ʧ��,pΪ��
				p->height--;//p���ֺ�,����ת��ڸ߶��½�
				solveDoubleBlack(p);//��������
			}
		}
	}
	else {//����ֵ�sΪ��,��p��s�ĺ��ӱ�Ȼ��Ϊ��
		s->color = RB_BLACK; p->color = RB_RED;
		BinNode<T>* t = IsLChild(*s) ? s->lChild : s->rChild;//ȡ���ֵ�sͬ��ĺ���,������3+4����,��s��Ϊ����,p��sͬ�ຢ�Ӹ߶�һ��
		this->_hot = p; FromParentTo(*p) = this->rotateAt(t);
		solveDoubleBlack(r);//������r����,��ʱr���¸����Ǻ�ɫ,���Դ�ʱr�����ֵ�s��Ϊ��ɫ,��ֻ��BB-1��BB-2R�����
	}
}