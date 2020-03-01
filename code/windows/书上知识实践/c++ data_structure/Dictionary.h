#pragma once

template<typename K,typename V>
struct Dictionary {
	virtual int size() const = 0;//��������
	virtual bool put(K k, V v) = 0;//����
	virtual V*get(K k) = 0;//��ȡ
	virtual bool remove(K k) = 0;//ɾ��
};