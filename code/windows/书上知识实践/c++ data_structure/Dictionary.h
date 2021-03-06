#pragma once

template<typename K,typename V>
struct Dictionary {
	virtual int size() const = 0;//词条总数
	virtual bool put(K k, V v) = 0;//插入
	virtual V*get(K k) = 0;//读取
	virtual bool remove(K k) = 0;//删除
};