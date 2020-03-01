#pragma once

#include <string>

//����next��,ע:�˴���Next����ǰ��׺��ͬ�ĸ���,����Ӧ�û��ݵ�����
int* buildNext(const char* P) {
	size_t m = std::strlen(P);
	int* Next = new int[m];
	Next[0] = -1;
	int j = 0;//ָ���׺���һ��Ԫ��
	int t = -1;//ָ��ǰ׺���һԪ��
	while (j < m-1) {
		if (0>t||P[t]==P[j]) {//�����ǰ��ƥ��
			t++; j++;
			Next[j] = (P[j] == P[t] ? Next[t]: t);//�жϴ�Ԫ�غ�ǰһ���Ƿ�һ��,��һ��,�����ʱû��Ҫ�ص�����,��Ϊֵ��һ��,��Ϊ��ֵ��Next����
		}
		else {
			t = Next[t];
		}
	}
	return Next;
}

//KMP�ַ���ƥ���㷨
int KMP_match(const char* P, const char* T) {
	int n = std::strlen(T);//�ı�������
	int m = std::strlen(P);//ƥ�䴮����
	int* Next = buildNext(P);
	int i = 0, j = 0;
	while (i < n&&j < m) {
		if (T[i] == P[j] || j < 0) {//���ƥ��ɹ�
			i++; j++;
		}
		else {
			j = Next[j];
		}
	}
	delete []Next;
	return i - j;
}