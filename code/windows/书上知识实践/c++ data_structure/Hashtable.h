#pragma once

#include "Dictionary.h"
#include "Bitmap.h"

//��ϣ��(���ɢ�б�)
template<typename K,typename V>
class Hashtable :public Dictionary<K, V> {
private:
	Entry<K, V>** ht;//Ͱ����,��Ŵ���ָ��
	int M;//Ͱ��������
	int N;//��������
	Bitmap* lazyRemoval;//����ɾ�����
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K&k);//�Ѳ�k,�����������Է��ض�Ӧ��Ͱ����
	int probe4Free(const K&k);//�Ѳ�k,�����������Է����׸���Ͱ
	void rehash();//����hash:����Ͱ����,����װ�������ھ���������
public:
	Hashtable(int c = 5);//���캯��,Ϊ����,Ĭ��ѡȡ��С��5,cΪͰ����
	~Hashtable();//����,�ͷ�Ͱ�����еĴ����Լ�Ͱ
	int size() const { return N; }//��ǰ�Ĵ�����Ŀ
	bool put(K k, V v);//����
	V* get(K k);//��ȡ
	bool remove(K k);//ɾ��
};

#include "Hashtable_inplenmentation.h"