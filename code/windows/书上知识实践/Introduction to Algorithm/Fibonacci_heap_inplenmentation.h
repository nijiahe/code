#pragma once

#include "fibonacci_heap.h"
#include <stack>
#include <queue>

#if 0
#define LOG2(x) ({ \
        unsigned int _i = 0; \
        __asm__("bsr %1, %0" : "=r" (_i) : "r" ((x))); \
        _i; })
#else   // ע�⣺ͨ��gcc����ʱ��Ҫ��� -lm ѡ�
#define LOG2(x) ((log((double)(x))) / (log(2.0)))
#endif

template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_search(T key);

/*
 * ����쳲�������
 */
template<typename T>
static FibHeap<T>* fib_heap_make(){
	FibHeap<T>* heap;

	heap = new FibHeap<T>;
	if (heap == nullptr){
		cout << "Error: make FibHeap failed" << endl;
		return nullptr;
	}

	heap->keyNum = 0;
	heap->maxDegree = 0;
	heap->min = nullptr;
	heap->cons = nullptr;

	return heap;
}

/*
 * ���ڵ�node���뵽쳲�������heap��
 */
template<typename T>
void FibHeap<T>::fib_heap_insert_node(FibNode<T> *node){
	if (keyNum == 0)
		min = node;
	else {
		node->fib_node_add_Before(min);
		if (node->key < min->key)
			min = node;
	}
	keyNum++;
}

/*
 * �½���ֵΪkey�Ľڵ㣬��������뵽쳲���������
 */
template<typename T>
void FibHeap<T>::fib_heap_insert_key(T key) {
	FibNode<T>* node;

	node = FibNode<T>::fib_node_make(key);
	if (node == nullptr)
		return;

	fib_heap_insert_node(node);
}

/*
 * ��h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
 */
template<typename T>
FibHeap<T>* FibHeap<T>::fib_heap_union(FibHeap *h1, FibHeap *h2) {
	FibHeap<T>* tmp;

	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;

	// ��h1Ϊ"ĸ"����h2���ӵ�h1�ϣ������Ǳ�֤h1�Ķ����󣬾����ܵ��ٲ�����
	if (h2->maxDegree > h1->maxDegree){
		tmp = h1;
		h1 = h2;
		h2 = tmp;
	}

	if ((h1->min) == nullptr) {  // h1��"��С�ڵ�"
		h1->min = h2->min;
		h1->keyNum = h2->keyNum;
		delete []h2->cons;
		delete h2;
	}
	else if ((h2->min) == NULL) { // h1��"��С�ڵ�" && h2��"��С�ڵ�"
		delete []h2->cons;
		delete h2;
	}  // h1��"��С�ڵ�" && h2��"��С�ڵ�"
	else {
		// ��"h2�и�����"��ӵ�"h1"��
		FibNode<T>::fib_node_cat(h1->min, h2->min);
		if (h1->min->key > h2->min->key)
			h1->min = h2->min;
		h1->keyNum += h2->keyNum;
		delete []h2->cons;
		delete h2;
	}
	return h1;
}

/*
 * ��"�ѵ���С���"�Ӹ��������Ƴ���
 * ����ζ��"����С�ڵ���������"�Ӷ����Ƴ�!(�����Ƴ�,���������min�͸���maxDegree֮���,�����ڲ��ӿ�)
 */
template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_remove_min() {
	FibNode<T>* min = min;

	if (min == min->right)//���ѵĸ��ڵ�������ֻ�������С�ڵ�
		min = nullptr;
	else {
		min->fib_node_remove();
		min = min->right;//�ݶ�Ϊ�ұߵ�?
	}
	min->left = min->right = min;

	return min;
}

/*
 * ����fib_heap_consolidate����ռ�
 */
template<typename T>
void FibHeap<T>::fib_heap_cons_make(){
	int old = maxDegree;

	// ����log2(x)��"+1"��ζ������ȡ����
	// ex. log2(13) = 3������ȡ��Ϊ3+1=4��
	maxDegree = LOG2(keyNum) + 1;

	// ���ԭ���ռ乻��,ֱ�ӷ��ؼ���
	if (old >= maxDegree)
		return;

	//������Ҫ���·����ڴ�
	if (cons)
		delete[]cons;
	// ��Ϊ��Ϊheap->maxDegree���ܱ��ϲ�������ҪmaxDegree+1
	cons = new FibNode<T>*[sizeof(FibNode<T> *) * (maxDegree + 1)];
}

/*
 * �ϲ�쳲������ѵĸ�������������ͬ��������
 */
template<typename T>
void FibHeap<T>::fib_heap_consolidate() {
	int i, d;
	FibNode<T> *x, *y, *tmp;

	fib_heap_cons_make();//���ٹ�ϣ���ÿռ�

	for (i = 0; i <= maxDegree; i++)	//���³�ʼ��
		cons[i] = nullptr;

	// �ϲ���ͬ�ȵĸ��ڵ㣬ʹÿ����������Ψһ
	while (min != nullptr) {
		x = fib_heap_remove_min();    // ȡ�����е���С��(��С�ڵ����ڵ���)
		d = x->degree;                    // ��ȡ��С���Ķ���
		// heap->cons[d] != nullptr����ζ����������(x��y)��"����"��ͬ,����Ҫ������С�ѵĹ�����кϲ�
		while (cons[d] != nullptr) {
			y = cons[d];            // y��"��x�Ķ�����ͬ����" 
			if (x->key > y->key) {        // ����keyС����Ϊ���ڵ�,key�����Ϊ�亢��
				tmp = x;
				x = y;
				y = tmp;
			}
			y->fib_heap_link_as_child(x);   // ��y���ӵ�x�ĺ�����
			cons[d] = nullptr;
			d++;							//�������൱����������һ�Ŷ��������1�Ķ�,��Ҫ�ٴαȽ�
		}
		cons[d] = x;					//�ȽϽ���,û������������ɵĶѶ���һ������,��������hash�����м�¼
	}
	min = nullptr;//��ʱ�˶���Ϊ��,���еĽڵ㶼��cons��

	// ��cons�еĽ�����¼ӵ�������,��������min�ڵ�
	for (i = 0; i <= maxDegree; i++) {
		if (cons[i] != nullptr) {
			if (min == nullptr)
				min = cons[i];
			else {
				cons[i]->fib_node_add_Before(min);
				if ((cons[i])->key < min->key)
					min = cons[i];
			}
		}
	}
}

/*
 * �Ƴ���С�ڵ㣬�������Ƴ��ڵ���쳲�������
 */
template<typename T>
FibNode<T>* FibHeap<T>::_fib_heap_extract_min() {
	FibNode<T>* c = nullptr;
	FibNode<T>* m = min;
	// ��minÿһ������(���ӺͶ��ӵ��ֵ�)����ӵ�"쳲������ѵĸ�����"��
	while (min->child != nullptr) {
		c = min->child;
		c->fib_node_remove();
		if (c->right == c)
			min->child = nullptr;
		else
			min->child = c->right;

		c->fib_node_add_Before(min);
	}

	// ��min�Ӹ��������Ƴ�
	min->fib_node_remove();
	// ��min�Ƕ���Ψһ�ڵ㣬�����öѵ���С�ڵ�ΪNULL��
	// �������öѵ���С�ڵ�Ϊһ���ǿսڵ�(min->right),Ȼ���ٽ��е���,���ϲ����ж�����ͬ�ĸ������еĽڵ�,��ȷ���µ�min
	if (min->right == min)
		min = nullptr;
	else {
		min = min->right;
		fib_heap_consolidate();	
	}
	keyNum--;

	return min;
}

//�Ƴ���С�ڵ�
template<typename T>
void FibHeap<T>::fib_heap_extract_min() {
	FibNode<T> *node;

	node = _fib_heap_extract_min();
	if (node != nullptr)
		delete node;
}

/*
 * ��ȡ��С�ڵ��Ӧ��ֵ(������key��);�ɹ�����true��ʧ�ܷ���false
 */
template<typename T>
bool FibHeap<T>::fib_heap_get_min(T& key) {
	if (min == nullptr)
		return false;

	key = min->key;
	return true;
}

/*
 * ��node�Ӹ��ڵ�parent���������а��������
 * ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
 */
template<typename T>
void FibHeap<T>::fib_heap_cut(FibNode<T>* node){
	node->fib_node_remove();

	node->left = node->right = node;
	node->marked = 0;
	// ��"node������"��ӵ�"������"��
	node->fib_node_add_Before(min);
}

/*
 * �Խڵ�node����"��������"
 *
 * �������У������С��Ľ���ƻ�����С�����ʣ�
 *     �����������(��������˫��������ɾ��������
 *     ����뵽����С�����ڵ��γɵ�˫��������)��
 *     Ȼ���ٴ�"���нڵ�ĸ��ڵ�"�����������ڵ�ݹ�ִ�м�����֦
 *
 * ���������֪��ʲô��˼
 */
template<typename T>
void FibHeap<T>::fib_heap_cascading_cut(FibNode<T>* node)
{
	FibNode<T>* parent = node->parent;
	if (parent == nullptr)//���Ѿ��Ǹ��ڵ�,���������
		return;

	if (node->marked == 0)//��һ��
		node->marked = 1;
	else{
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);//�ݹ���
	}
}

/*
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
 */
template<typename T>
void FibHeap<T>::fib_heap_decrease(FibNode<T>* node, T key)
{
	FibNode<T>* parent;

	if (min == nullptr || node == nullptr)
		return;

	if (key >= node->key){
		cout << "decrease failed: the new key(" << key << ") is no smaller than current key(" << node->key << ")" << endl;
		return;
	}

	node->key = key;
	parent = node->parent;
	if (parent != nullptr && node->key < parent->key) {
		// ��node�Ӹ��ڵ�parent�а������������node��ӵ���������
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);//���˲��Ǹ�������±��г�����,��һ��marked��Ϊ1,�ڶ�����Ҫʹ���Ϊһ���µĸ�
	}

	// ������С�ڵ�
	if (node->key < min->key)
		min = node;
}

/*
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
 */
template<typename T>
void FibHeap<T>::fib_heap_increase(FibNode<T>* node, T key){
	FibNode<T> *child, *parent, *right;

	if (min == nullptr || node == nullptr)
		return;

	if (key <= node->key){
		printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
		return;
	}

	// ��nodeÿһ������(����������,����,...)����ӵ�"쳲������ѵĸ�����"��
	while (node->child != nullptr){
		child = node->child;
		child->fib_node_remove();               // ��child��node����������ɾ��

		child->fib_node_add_Before(min);       // ��child��ӵ���������
		child->parent = nullptr;
	}
	node->key = key;

	// ���node���ڸ������У�
	//     ��node�Ӹ��ڵ�parent���������а��������
	//     ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
	//     Ȼ�����"��������"
	// �������ж��Ƿ���Ҫ���¶ѵ���С�ڵ�
	parent = node->parent;
	if (parent != nullptr){//node���ڸ��ڵ���,����node��Ϊ�������һԱ,�ڽ��м�������
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);
	}
	else if (min == node){//��nodeԭ����min�ڵ�,��Ҫȷ���µ�min�ڵ�
		right = node->right;
		while (right != node){
			if (node->key > right->key)
				min = right;
			right = right->right;
		}
	}
}

/*
 * ���¶����heap�Ľڵ�node�ļ�ֵΪkey
 */
template<typename T>
void FibHeap<T>::_fib_heap_update(FibNode<T>* node, T key){
	if (key < node->key)
		fib_heap_decrease(node, key);
	else if (key > node->key)
		fib_heap_increase(node, key);
	else
		printf("No need to update!!!\n");
}

template<typename T>
void FibHeap<T>::fib_heap_update(T oldkey, T newkey) {
	FibNode<T>* node;

	node = fib_heap_search(oldkey);
	if (node != nullptr)
		_fib_heap_update(node, newkey);
}


/*
 * ��쳲�������heap�в��Ҽ�ֵΪkey�Ľڵ�
 */
template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_search(T k) {
	if (!min)
		return nullptr;

	FibNode<T>* f = min;		//���ÿһ���������еĽڵ�
	FibNode<T>* p = nullptr;	//���ÿ���ڵ�ķ���ֵ
	do {
		p = f->fib_node_search(k);
		if (!p)
			break;
		f = f->right;
	} while (f != min);
	return p;
}

/*
 * ��쳲�������heap���Ƿ���ڼ�ֵΪkey�Ľڵ㡣
 * ���ڷ���true�����򷵻�false��
 */
template<typename T>
bool FibHeap<T>::fib_heap_contains(T k) {
	return fib_heap_search(k) != nullptr ? true : false;
}

/*
 * ɾ�����node
 */
template<typename T>
void FibHeap<T>::_fib_heap_delete(FibNode<T>* node) {
	fib_heap_decrease(node, min->key - 1);
	fib_heap_extract_min();
}

template<typename T>
void FibHeap<T>::fib_heap_delete(T key){
	FibNode<T>* node;

	if (min == nullptr)
		return;

	node = fib_heap_search(key);
	if (node == nullptr)
		return;

	_fib_heap_delete(node);
}

/*
 * ɾ���ͷ����нڵ�,���ѱ�Ϊ�մ���ʱ������
 */
template<typename T>
void FibHeap<T>::fib_heap_destroy_all_node(){
	stack<FibNode<T>*> s;//�Ե����ϴ��Ԫ�ش�ɾ��Ԫ��
	queue<FibNode<T>*> q;//���ÿһ��Ԫ��

	if (!min) {//�����Ϊ��
		delete []cons;
		return;
	}

	FibNode<T>* beg = min;
	FibNode<T>* temp = min;
	
	//�ȰѸ�����ڵ�ȫ���ӽ�ȥ
	do {
		q.push(temp);
		s.push(temp);
		temp = temp->right;
	} while (temp != beg);
	
	while (!q.empty()) {
		beg = temp = q.front()->child; q.pop();//��ÿ���ڵ�ĺ�����ȫ��ѹ��
		if (temp == nullptr)
			continue;
		do {
			q.push(temp);
			s.push(temp);
			temp = temp->right;
		} while (temp != beg);
	}
	while (!s.empty()) {//�Ե�����ɾ�����нڵ�
		delete(s.top()); s.pop();
	}

	//ɾ����ϣ
	delete[]cons;
	return;
}

//�����������ǰӦ���ȵ���destroy_all_node
template<typename T>
static void FibHeap<T>::fib_heap_destroy(FibHeap *heap){
	free(heap);
}

/*
 *��ӡ쳲�������
 */
template<typename T>
static void FibHeap<T>::fib_print(FibHeap<T> *heap) {
	if (heap == nullptr || heap->min == nullptr)
		return;

	cout << "== 쳲������ѵ���ϸ��Ϣ: ==\n" << endl;

	queue<FibNode<T>*> q;//���ÿһ��Ԫ��

	FibNode<T>* beg = heap->min;
	FibNode<T>* temp = heap->min;

	//�ȰѸ�����ڵ�ȫ���ӽ�ȥ
	cout << "The root list:min->";
	do {
		cout << temp->key << "->";
		q.push(temp);
		temp = temp->right;
	} while (temp != beg);
	cout << "first" << endl;

	while (!q.empty()) {
		beg = temp = q.front()->child; q.pop();//��ÿ���ڵ�ĺ�����ȫ��ѹ��
		if (temp == nullptr)
			continue;
		cout << "parent is " << temp->parent << ",parent's child:";
		do {
			cout << temp->key << "->";
			q.push(temp);
			temp = temp->right;
		} while (temp != beg);
		cout << "first" << endl;
	}
}