#include "common.h"

//next[k]表示前k-1个元素的与后缀相匹配的元素个数
/*
比如T为:....abc....abe....abd
...abd后缀可以和...abe相匹配,但是e和d不匹配,所以寻找上一个ab...进行匹配
*/
void buildNext(const char* P, int* next, int len) {
	next[0] = -1;
	int i = -1, j = 0;//-1指向前缀最后一个字符,j指向后缀最后一个字符
	//数学归纳法,在已有的条件下,为下一个字符生成next
	while (j < len - 1) {
		if (i < 0 || P[i] == P[j]){
			i++; j++;
			next[j] = (P[j] == P[i] ? next[i] : i);//如果比对T[j]的时候错了,T[i]又和T[j]一样,那next数组设为i就没用了
		}
		else {
			i = next[i];
		}
	}
}

//KMP算法,通过构建next表来优化匹配失败后的前进步数,P为主串,T为匹配串,返回子串在主串中的位置,若返回-1,表示主串中不存在子串
int KMP(const char* T, const char* P) {
	int T_len = strlen(T);
	int P_len = strlen(P);
	if (P_len == 0 || T_len == 0)
		return -1;
	int* next = new int[P_len];
	buildNext(P, next, P_len);
	int i = 0, j = 0;//i是T的指针,j是P的指针
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