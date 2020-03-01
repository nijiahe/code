#pragma once

template<typename K,typename V>//词条类,即键值对类
struct Entry {
	K key;
	V value;

	Entry(K k = K(), V v = V()) :key(k), value(v) {};//默认构造
	Entry(Entry<K, V> const &e) :key(e.key), value(e.value) {};//克隆

	bool operator<(Entry<K, V> const &e) { return key < e.key; }
	bool operator>(Entry<K, V> const &e) { return key > e.key; }
	bool operator==(Entry<K, V> const &e) { return key == e.key; }
	bool operator!=(Entry<K, V> const &e) { return key != e.key; }
};