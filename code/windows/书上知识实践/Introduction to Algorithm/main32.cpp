#include "common.h"

//next[k]��ʾǰk-1��Ԫ�ص����׺��ƥ���Ԫ�ظ���
/*
����TΪ:....abc....abe....abd
...abd��׺���Ժ�...abe��ƥ��,����e��d��ƥ��,����Ѱ����һ��ab...����ƥ��
*/
void buildNext(const char* P, int* next, int len) {
	next[0] = -1;
	int i = -1, j = 0;//-1ָ��ǰ׺���һ���ַ�,jָ���׺���һ���ַ�
	//��ѧ���ɷ�,�����е�������,Ϊ��һ���ַ�����next
	while (j < len - 1) {
		if (i < 0 || P[i] == P[j]){
			i++; j++;
			next[j] = (P[j] == P[i] ? next[i] : i);//����ȶ�T[j]��ʱ�����,T[i]�ֺ�T[j]һ��,��next������Ϊi��û����
		}
		else {
			i = next[i];
		}
	}
}

//KMP�㷨,ͨ������next�����Ż�ƥ��ʧ�ܺ��ǰ������,PΪ����,TΪƥ�䴮,�����Ӵ��������е�λ��,������-1,��ʾ�����в������Ӵ�
int KMP(const char* T, const char* P) {
	int T_len = strlen(T);
	int P_len = strlen(P);
	if (P_len == 0 || T_len == 0)
		return -1;
	int* next = new int[P_len];
	buildNext(P, next, P_len);
	int i = 0, j = 0;//i��T��ָ��,j��P��ָ��
	while (i < T_len&&j < P_len) {
		if (j < 0 || T[i] == P[j]) {
			i++; j++;
		}
		else
			j = next[j];
	}
	delete[]next;
	if (j == P_len)
		return i - j;
	else return -1;

}

int main32() {
	const char* T = "abcabcba,bcabcbabcba,babcbaabcab,ababacbaba,bcbacb,acbabc,ababc,cbabcaabc";
	const char* P = "abcab,ababa";
	std::cout << std::endl;
	int num = KMP(T, P);
	std::cout << T + num << std::endl;

	return 0;
}