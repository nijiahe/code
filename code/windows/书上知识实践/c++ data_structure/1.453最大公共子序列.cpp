#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

#define N 256
using namespace std;
int dp[N][N];

//�������ӦΪstr,n-1
/*һ�㷽��������һ��m*n�ı�񣬱��Խ���Ͻ�Խ�ᱻ���Ѷ�Σ����m=n�����Ӷ�ΪO(2^n)*/
int LCS1(char A[],char B[],int m,int n){
	if (m < 0 || n < 0)return 0;
	else if (A[m] == B[n])return 1 + LCS1(A, B, m - 1, n - 1);
	else {
		return max(LCS1(A, B, m - 1, n),LCS1(A, B, m, n - 1));
	}
}

int LCS2(char A[], char B[], int m, int n) {
	int leng = m + 2;
	int wid = n + 2;
	memset(dp, 0, N*N*sizeof(int));
	for (int i = 1; i < wid; i++){
		for (int j = 1; j < leng; j++) {
			if (B[i-1] == A[j-1])dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j-1]);
		}
	}
	return dp[wid-1][leng-1];
}

int main1_453()
{
	char str1[] = "program";
	char str2[] = "algorithm";
	cout << LCS2(str1, str2, strlen(str1) - 1, strlen(str2) - 1) << endl;

	system("pause");
	return 0;
}