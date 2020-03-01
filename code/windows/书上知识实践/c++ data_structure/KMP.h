#pragma once

#include <string>

//构造next表,注:此处的Next表不是前后缀相同的个数,而是应该回溯到哪里
int* buildNext(const char* P) {
	size_t m = std::strlen(P);
	int* Next = new int[m];
	Next[0] = -1;
	int j = 0;//指向后缀最后一个元素
	int t = -1;//指向前缀最后一元素
	while (j < m-1) {
		if (0>t||P[t]==P[j]) {//如果当前的匹配
			t++; j++;
			Next[j] = (P[j] == P[t] ? Next[t]: t);//判断此元素和前一个是否一致,若一致,则回溯时没必要回到这里,因为值都一样,记为此值的Next即可
		}
		else {
			t = Next[t];
		}
	}
	return Next;
}

//KMP字符串匹配算法
int KMP_match(const char* P, const char* T) {
	int n = std::strlen(T);//文本串长度
	int m = std::strlen(P);//匹配串长度
	int* Next = buildNext(P);
	int i = 0, j = 0;
	while (i < n&&j < m) {
		if (T[i] == P[j] || j < 0) {//如果匹配成功
			i++; j++;
		}
		else {
			j = Next[j];
		}
	}
	delete []Next;
	return i - j;
}