#pragma once

#include "Dictionary.h"
#include "Bitmap.h"

//哈希表(或称散列表)
template<typename K,typename V>
class Hashtable :public Dictionary<K, V> {
private:
	Entry<K, V>** ht;//桶数组,存放词条指针
	int M;//桶数组容量
	int N;//词条数量
	Bitmap* lazyRemoval;//懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K&k);//搜查k,按照搜索策略返回对应的桶的秩
	int probe4Free(const K&k);//搜查k,按照搜索策略返回首个空桶
	void rehash();//重新hash:扩充桶数组,保持装填因子在警戒线以下
public:
	Hashtable(int c = 5);//构造函数,为测试,默认选取较小的5,c为桶数量
	~Hashtable();//析构,释放桶数组中的词条以及桶
	int size() const { return N; }//当前的词条数目
	bool put(K k, V v);//插入
	V* get(K k);//读取
	bool remove(K k);//删除
};

#include "Hashtable_inplenmentation.h"