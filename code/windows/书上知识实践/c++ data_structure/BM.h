#pragma once

#include <string>
#include <algorithm>

int* buildBC(const char* P) {
	int* BC = new int[256];
	size_t m = std::strlen(P);
	for (size_t i = 0; i < 256; i++)
		BC[i] = -1;//��ʼ��,�൱��memset��-1,-1��ʾͨ���
	for (size_t i = 0; i < m; i++)
		BC[P[i]] = i;//��¼ÿ���ַ���������λ��
	return BC;
}

//ss�� ���ƥ���׺�ַ���
int* buildSS(const char* P) {
	int m = strlen(P);
	int* ss = new int[m];
	ss[m - 1] = m;//�����һ���ַ�����,���ƥ���׺�����ַ�������
	int lo = m - 1, hi = m - 1;//P(lo,hi]��p[m-hi+lo,m)��ʾ��ǰƥ�䴮
	for (int j = m - 2; j >= 0; j--) {//���һ��Ԫ�ص�ssֵ�Ѿ�ȷ��,���Դӵ����ڶ���Ԫ�ؿ�ʼ
		if ((lo < j) && (ss[m - 1 - (hi - j)] <= j - lo))//��lo<j,�������ǰ����һ��ʹ��һ���������׺�໥ƥ��,��˺����Ĵ���β����һ��һ��
			//ֻ��β����ƥ��Ĵ������ڵ�ǰƥ��Ĵ��ĳ���,��(ss[m - 1 - (hi - j)] <= j - lo),�����ֱ������β����ȡ�õ���ֵ
			ss[j] = ss[m - 1 -(hi-j)];
		else {
			hi = j; lo = __min(lo, hi);//�ѵ�˵ֻ����ƥ����ַ�Ϊͬһ��ʱ���п��ܷ���(ss[m - 1 - (hi - j)] > j - lo)?
			//������ô��Ϊ,��Ȼ���벻ͨ����Ϊʲôlo=__min(lo,hi),��Ϊhi������,loȴ����ԭ���ĵĻ�,�������ȫ��Ϊͳһ�ַ�,��ô��֤���ͺ�׺ƥ��?
			while ((0 <= lo) && (P[m - 1 - (hi - lo)] == P[lo])) //�����һ��Ԫ�����׺��һ��Ԫ�����,��������
				lo--;//ƥ����½�--
			ss[j] = hi - lo;//����
		}
	}
	return ss;
}

int* buildGS(const char* P) {
	int m = std::strlen(P);
	int* gs = new int[m];
	int* ss = buildSS(P);
	for (int j = 0; j < m; j++)gs[j] = m;//Ĭ�϶���m������
	for (int j = m - 1,i = 0; j >= 0;j--) {//����ɨ��,�����ӿ������ƶ�����ĸ����ƶ���С��
		if (j + 1 == ss[j]) //���a,�����ǰj��ss��ֱ�ӵ�ͷ��,j + 1��ʾ[0,j]�ĳ���,ss[j]��ʾj��Ԫ��ǰ����β����׺�����ƥ�䳤��
			while (i < m - (j + 1))//�������е��ȴ���j,<m��Ԫ��,����ƶ�m-(j+1)������һ��ѡ����Ϊ��ЩԪ�ض�����������������β��
				gs[i++] = m - j - 1;
	}
	for (size_t j = 0; j < m - 1; j++)//���b,�����㷨
		gs[m - ss[j] - 1] = m - j - 1;//��ss���¼����Ϣ��һ�θ���,����m-ss[j]-1��ʧ��,����Ӧ�Ľ�j�Ƶ�m-1��λ����,���ƶ�m-1-j
	delete[]ss;
	return gs;
}

//BM�㷨,���Bad Character���ַ���Good Suffix�ú�׺
int BM_match(const char* P, const char* T) {
	int* bc = buildBC(P);//���ַ���
	int* gs = buildGS(P);//�ú�׺��
	size_t i = 0;//ģʽ�����ı�����ϵ�ƫ��
	while (std::strlen(T) >= i + strlen(P)) {//��ģʽ��û���Ƴ�ͷ
		int j = strlen(P)-1;//��ģʽ�����ƶ���ָ��,��ģʽ�����ʼ
		while (P[j] == T[i + j])//ƥ��
			if (--i < 0)break;//ȫ��ƥ��,��break��ǰѭ��,��Ϊ�Ѿ�ƥ�������
		if (j < 0)//ƥ�����
			break;
		else
			i += std::max(gs[j], j - bc[T[i + j]]);//���������еĸ�����
	}
	delete[]gs; delete[]bc;
	return i;
}