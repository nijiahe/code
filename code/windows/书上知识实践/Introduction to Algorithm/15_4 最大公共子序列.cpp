#include "common.h"
#include <string>

inline int xyToValue(int* lcs, int x, int i, int j) {
	if ((0 > i) || (0 > j)) {//������������ĵ���0
		return 0;
	}
	return lcs[i*x + j];
}

//���������ַ���,�õ����ǵ���󹫹������д����s��,���س���,O(n^2)�㷨
int LCS_Length(const char* str1, const char* str2,string* s) {
	size_t x = strlen(str1);//str1��Ϊx��
	size_t y = strlen(str2);//str2��Ϊy��
	int* lcs = new int[x*y];//������������г��ȵĶ�ά����
	int now_max_length = -1;
	for (unsigned int i = 0; i < y; i++) {
		for (unsigned int j = 0; j < x; j++) {
			if (str1[j] != str2[i])
				lcs[i*x + j] = std::max(xyToValue(lcs, x, i - 1, j), xyToValue(lcs, x, i, j - 1));
			else {
				lcs[i*x + j] = 1 + xyToValue(lcs, x, i - 1, j - 1);//�����ǰ�����,����������ַ�����ȥ�����һ���ַ������󹫹������г���+1
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
	//�������ó��Ķ�ά�������õ�LCS:��������������������,�����ַ�ѹ��ջ��,��������ߺ��ϱߺ��Լ�ֵ��ȵĵط���
	int x_beg = x - 1, y_beg = y - 1;
	while (xyToValue(lcs, x, y_beg,x_beg) > 0) {
		if (xyToValue(lcs, x, y_beg, x_beg) == xyToValue(lcs, x, y_beg - 1, x_beg)) {//������
			y_beg--;
		}
		else if(xyToValue(lcs, x, y_beg, x_beg) == xyToValue(lcs, x, y_beg, x_beg - 1)) {//������
			x_beg--;
		}
		else  {//����϶��߲���,˵����ά�����е����ֵ�Ǵ�����+1������,��������
			s->push_back(str1[x_beg]);//��ʱstr1[x_beg]==str2[y_beg]
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