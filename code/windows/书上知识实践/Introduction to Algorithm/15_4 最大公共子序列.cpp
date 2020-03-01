#include "common.h"
#include <string>

inline int xyToValue(int* lcs, int x, int i, int j) {
	if ((0 > i) || (0 > j)) {//落在数组外面的当作0
		return 0;
	}
	return lcs[i*x + j];
}

//输入两个字符串,得到他们的最大公共子序列存放在s内,返回长度,O(n^2)算法
int LCS_Length(const char* str1, const char* str2,string* s) {
	size_t x = strlen(str1);//str1作为x轴
	size_t y = strlen(str2);//str2作为y轴
	int* lcs = new int[x*y];//创建存放子序列长度的二维数组
	int now_max_length = -1;
	for (unsigned int i = 0; i < y; i++) {
		for (unsigned int j = 0; j < x; j++) {
			if (str1[j] != str2[i])
				lcs[i*x + j] = std::max(xyToValue(lcs, x, i - 1, j), xyToValue(lcs, x, i, j - 1));
			else {
				lcs[i*x + j] = 1 + xyToValue(lcs, x, i - 1, j - 1);//如果当前数相等,则等于两个字符串均去掉左后一个字符后的最大公共子序列长度+1
			}			
		}
	}
#ifdef _DEBUG
	//log array
	cout << setw(4) << " ";
	for (int i = 0; i < x; i++)
		cout << setw(4) << str1[i];
	cout << endl;
	for (int i = 0; i < y; i++) {
		cout << setw(4) << str2[i];
		for (int j = 0; j < x; j++) {
			cout << setw(4) << xyToValue(lcs, x, i, j);
		}
		cout << endl;
	}
#endif
	//根据最后得出的二维数组来得到LCS:若能往左上则往左上走,并把字符压入栈中,否则往左边和上边和自己值相等的地方走
	int x_beg = x - 1, y_beg = y - 1;
	while (xyToValue(lcs, x, y_beg,x_beg) > 0) {
		if (xyToValue(lcs, x, y_beg, x_beg) == xyToValue(lcs, x, y_beg - 1, x_beg)) {//往上走
			y_beg--;
		}
		else if(xyToValue(lcs, x, y_beg, x_beg) == xyToValue(lcs, x, y_beg, x_beg - 1)) {//往左走
			x_beg--;
		}
		else  {//左和上都走不了,说明二维数组中的这个值是从左上+1得来的,往左上走
			s->push_back(str1[x_beg]);//此时str1[x_beg]==str2[y_beg]
			x_beg--; y_beg--;
		}
	}
	reverse(s->begin(), s->end());
	int val = xyToValue(lcs, x, y - 1, x - 1);
	delete[]lcs;
	return val;
}

int main15_4() {
	const char* str1 = "ab123ab456ab";
	const char* str2 = "ca2b4c6ac";
	string s;
	int n = LCS_Length(str1, str2, &s);
	cout << "The length of longest-common-subsequence is " << n << ",and it is \"" << s << "\""<<endl;

	return 0;
}