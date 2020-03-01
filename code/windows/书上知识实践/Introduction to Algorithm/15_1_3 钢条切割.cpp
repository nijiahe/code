#include "common.h"

#define STEEL_TABLE_SIZE 11

static int steel_price[STEEL_TABLE_SIZE] =	{ 0,1,5,8,9,10,17,17,20,24,30 };

void log_section(int* section, int l) {
	cout << "start log sections:" << endl;
	while (l > 0) {
		cout << section[l] << " ";
		l -= section[l];
	}
	cout << endl;
	cout << "log finished"<<endl;
}

//����������Ⱥ�ÿ���и������ѵ�Ǯ,�õ�����и�׬��Ǯ
int get_optical_price(int l,int c) {
	int* max_cut_price = new int[l + 1];//������ż۸�
	int* first_section = new int[l + 1];//��ŵ�һ���и�����ĳ���
	//��ʼ���۸�
	for (int i = 0; i < STEEL_TABLE_SIZE; i++)
		max_cut_price[i] = -1;
	max_cut_price[0] = 0;
	//��ʼ����һ�γ���
	for (int i = 0; i < STEEL_TABLE_SIZE; i++)
		first_section[i] = 0;
	for (int i = 1; i <= l; i++) {//����max_cut_price[i]
		for (int j = 1;j<i ; j++) {//���ж��Ƿ���Ҫ�и�
			int s = max_cut_price[j] + max_cut_price[i - j] - c;
			if (s > max_cut_price[i]) {//����ȵ�ǰ�Ľ����,�����
				max_cut_price[i] = s;
				first_section[i] = j;
			}
		}
		//���жϲ���Ҫ�и�����
		if (i <= STEEL_TABLE_SIZE - 1) {//����ܲ���Ҫ�и�
			int s = steel_price[i];
			if (s > max_cut_price[i]) {//����ȵ�ǰ�Ľ����,�����
				max_cut_price[i] = s;
				first_section[i] = i;
			}
		}
	}
	log_section(first_section,l);
#ifdef _DEBUG
	//log max_cut price array
	cout << "log array:" << endl;
	for (int i = 0; i <= l; i++) {
		cout << "The steel's length is " << i << ",the price is " << max_cut_price[i] << endl;
	}
	cout << "log array finished" << endl;
#endif
	
	return max_cut_price[l];
}

int main15_1_3() {
	int s = get_optical_price(29, 1);//��20�ĸֽ�,ÿ���и�۸�Ϊ2
	cout << "The optical price is " << s << endl;

	return 0;
}