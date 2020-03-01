#pragma once

#include "fibonacci_heap.h"
#include <stack>
#include <queue>

#if 0
#define LOG2(x) ({ \
        unsigned int _i = 0; \
        __asm__("bsr %1, %0" : "=r" (_i) : "r" ((x))); \
        _i; })
#else   // 注意：通过gcc编译时，要添加 -lm 选项。
#define LOG2(x) ((log((double)(x))) / (log(2.0)))
#endif

template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_search(T key);

/*
 * 创建斐波那契堆
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
 * 将节点node插入到斐波那契堆heap中
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
 * 新建键值为key的节点，并将其插入到斐波那契堆中
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
 * 将h1, h2合并成一个堆，并返回合并后的堆
 */
template<typename T>
FibHeap<T>* FibHeap<T>::fib_heap_union(FibHeap *h1, FibHeap *h2) {
	FibHeap<T>* tmp;

	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;

	// 以h1为"母"，将h2附加到h1上；下面是保证h1的度数大，尽可能的少操作。
	if (h2->maxDegree > h1->maxDegree){
		tmp = h1;
		h1 = h2;
		h2 = tmp;
	}

	if ((h1->min) == nullptr) {  // h1无"最小节点"
		h1->min = h2->min;
		h1->keyNum = h2->keyNum;
		delete []h2->cons;
		delete h2;
	}
	else if ((h2->min) == NULL) { // h1有"最小节点" && h2无"最小节点"
		delete []h2->cons;
		delete h2;
	}  // h1有"最小节点" && h2有"最小节点"
	else {
		// 将"h2中根链表"添加到"h1"中
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
 * 将"堆的最小结点"从根链表中移除，
 * 这意味着"将最小节点所属的树"从堆中移除!(仅仅移除,不负责更新min和更新maxDegree之类的,属于内部接口)
 */
template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_remove_min() {
	FibNode<T>* min = min;

	if (min == min->right)//若堆的根节点链表中只有这个最小节点
		min = nullptr;
	else {
		min->fib_node_remove();
		min = min->right;//暂定为右边的?
	}
	min->left = min->right = min;

	return min;
}

/*
 * 创建fib_heap_consolidate所需空间
 */
template<typename T>
void FibHeap<T>::fib_heap_cons_make(){
	int old = maxDegree;

	// 计算log2(x)，"+1"意味着向上取整！
	// ex. log2(13) = 3，向上取整为3+1=4。
	maxDegree = LOG2(keyNum) + 1;

	// 如果原本空间够了,直接返回即可
	if (old >= maxDegree)
		return;

	//否则需要重新分配内存
	if (cons)
		delete[]cons;
	// 因为度为heap->maxDegree可能被合并，所以要maxDegree+1
	cons = new FibNode<T>*[sizeof(FibNode<T> *) * (maxDegree + 1)];
}

/*
 * 合并斐波那契堆的根链表中左右相同度数的树
 */
template<typename T>
void FibHeap<T>::fib_heap_consolidate() {
	int i, d;
	FibNode<T> *x, *y, *tmp;

	fib_heap_cons_make();//开辟哈希所用空间

	for (i = 0; i <= maxDegree; i++)	//重新初始化
		cons[i] = nullptr;

	// 合并相同度的根节点，使每个度数的树唯一
	while (min != nullptr) {
		x = fib_heap_remove_min();    // 取出堆中的最小树(最小节点所在的树)
		d = x->degree;                    // 获取最小树的度数
		// heap->cons[d] != nullptr，意味着有两棵树(x和y)的"度数"相同,则需要按照最小堆的规则进行合并
		while (cons[d] != nullptr) {
			y = cons[d];            // y是"与x的度数相同的树" 
			if (x->key > y->key) {        // 即将key小的作为根节点,key大的作为其孩子
				tmp = x;
				x = y;
				y = tmp;
			}
			y->fib_heap_link_as_child(x);   // 将y链接到x的孩子中
			cons[d] = nullptr;
			d++;							//这样就相当于又生成了一颗度数多加了1的堆,需要再次比较
		}
		cons[d] = x;					//比较结束,没有与这个新生成的堆度数一样的了,将其置入hash数组中记录
	}
	min = nullptr;//此时此堆中为空,所有的节点都在cons里

	// 将cons中的结点重新加到根表中,并检查更新min节点
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
 * 移除最小节点，并返回移除节点后的斐波那契堆
 */
template<typename T>
FibNode<T>* FibHeap<T>::_fib_heap_extract_min() {
	FibNode<T>* c = nullptr;
	FibNode<T>* m = min;
	// 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
	while (min->child != nullptr) {
		c = min->child;
		c->fib_node_remove();
		if (c->right == c)
			min->child = nullptr;
		else
			min->child = c->right;

		c->fib_node_add_Before(min);
	}

	// 将min从根链表中移除
	min->fib_node_remove();
	// 若min是堆中唯一节点，则设置堆的最小节点为NULL；
	// 否则，设置堆的最小节点为一个非空节点(min->right),然后再进行调节,即合并所有度数相同的根链表中的节点,并确定新的min
	if (min->right == min)
		min = nullptr;
	else {
		min = min->right;
		fib_heap_consolidate();	
	}
	keyNum--;

	return min;
}

//移除最小节点
template<typename T>
void FibHeap<T>::fib_heap_extract_min() {
	FibNode<T> *node;

	node = _fib_heap_extract_min();
	if (node != nullptr)
		delete node;
}

/*
 * 获取最小节点对应的值(保存在key中);成功返回true，失败返回false
 */
template<typename T>
bool FibHeap<T>::fib_heap_get_min(T& key) {
	if (min == nullptr)
		return false;

	key = min->key;
	return true;
}

/*
 * 将node从父节点parent的子链接中剥离出来，
 * 并使node成为"堆的根链表"中的一员。
 */
template<typename T>
void FibHeap<T>::fib_heap_cut(FibNode<T>* node){
	node->fib_node_remove();

	node->left = node->right = node;
	node->marked = 0;
	// 将"node所在树"添加到"根链表"中
	node->fib_node_add_Before(min);
}

/*
 * 对节点node进行"级联剪切"
 *
 * 级联剪切：如果减小后的结点破坏了最小堆性质，
 *     则把它切下来(即从所在双向链表中删除，并将
 *     其插入到由最小树根节点形成的双向链表中)，
 *     然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
 *
 * 这个函数不知道什么意思
 */
template<typename T>
void FibHeap<T>::fib_heap_cascading_cut(FibNode<T>* node)
{
	FibNode<T>* parent = node->parent;
	if (parent == nullptr)//若已经是根节点,则无需计数
		return;

	if (node->marked == 0)//第一次
		node->marked = 1;
	else{
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);//递归标记
	}
}

/*
 * 将斐波那契堆heap中节点node的值减少为key
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
		// 将node从父节点parent中剥离出来，并将node添加到根链表中
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);//若此不是根的情况下被切除孩子,第一次marked记为1,第二次需要使其成为一个新的根
	}

	// 更新最小节点
	if (node->key < min->key)
		min = node;
}

/*
 * 将斐波那契堆heap中节点node的值增加为key
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

	// 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
	while (node->child != nullptr){
		child = node->child;
		child->fib_node_remove();               // 将child从node的子链表中删除

		child->fib_node_add_Before(min);       // 将child添加到根链表中
		child->parent = nullptr;
	}
	node->key = key;

	// 如果node不在根链表中，
	//     则将node从父节点parent的子链接中剥离出来，
	//     并使node成为"堆的根链表"中的一员，
	//     然后进行"级联剪切"
	// 否则，则判断是否需要更新堆的最小节点
	parent = node->parent;
	if (parent != nullptr){//node不在根节点中,则让node成为根链表的一员,在进行级联剪切
		fib_heap_cut(node);
		fib_heap_cascading_cut(parent);
	}
	else if (min == node){//若node原先是min节点,需要确定新的min节点
		right = node->right;
		while (right != node){
			if (node->key > right->key)
				min = right;
			right = right->right;
		}
	}
}

/*
 * 更新二项堆heap的节点node的键值为key
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
 * 在斐波那契堆heap中查找键值为key的节点
 */
template<typename T>
FibNode<T>* FibHeap<T>::fib_heap_search(T k) {
	if (!min)
		return nullptr;

	FibNode<T>* f = min;		//存放每一个根链表中的节点
	FibNode<T>* p = nullptr;	//存放每个节点的返回值
	do {
		p = f->fib_node_search(k);
		if (!p)
			break;
		f = f->right;
	} while (f != min);
	return p;
}

/*
 * 在斐波那契堆heap中是否存在键值为key的节点。
 * 存在返回true，否则返回false。
 */
template<typename T>
bool FibHeap<T>::fib_heap_contains(T k) {
	return fib_heap_search(k) != nullptr ? true : false;
}

/*
 * 删除结点node
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
 * 删除释放所有节点,将堆变为刚创建时的样子
 */
template<typename T>
void FibHeap<T>::fib_heap_destroy_all_node(){
	stack<FibNode<T>*> s;//自底向上存放元素待删除元素
	queue<FibNode<T>*> q;//存放每一行元素

	if (!min) {//如果堆为空
		delete []cons;
		return;
	}

	FibNode<T>* beg = min;
	FibNode<T>* temp = min;
	
	//先把根链表节点全部加进去
	do {
		q.push(temp);
		s.push(temp);
		temp = temp->right;
	} while (temp != beg);
	
	while (!q.empty()) {
		beg = temp = q.front()->child; q.pop();//将每个节点的孩子再全部压入
		if (temp == nullptr)
			continue;
		do {
			q.push(temp);
			s.push(temp);
			temp = temp->right;
		} while (temp != beg);
	}
	while (!s.empty()) {//自底向上删除所有节点
		delete(s.top()); s.pop();
	}

	//删除哈希
	delete[]cons;
	return;
}

//调用这个函数前应该先调用destroy_all_node
template<typename T>
static void FibHeap<T>::fib_heap_destroy(FibHeap *heap){
	free(heap);
}

/*
 *打印斐波那契堆
 */
template<typename T>
static void FibHeap<T>::fib_print(FibHeap<T> *heap) {
	if (heap == nullptr || heap->min == nullptr)
		return;

	cout << "== 斐波那契堆的详细信息: ==\n" << endl;

	queue<FibNode<T>*> q;//存放每一行元素

	FibNode<T>* beg = heap->min;
	FibNode<T>* temp = heap->min;

	//先把根链表节点全部加进去
	cout << "The root list:min->";
	do {
		cout << temp->key << "->";
		q.push(temp);
		temp = temp->right;
	} while (temp != beg);
	cout << "first" << endl;

	while (!q.empty()) {
		beg = temp = q.front()->child; q.pop();//将每个节点的孩子再全部压入
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