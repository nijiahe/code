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

//输入钢条长度和每次切割所花费的钱,得到最佳切割赚的钱
int get_optical_price(int l,int c) {
	int* max_cut_price = new int[l + 1];//存放最优价格
	int* first_section = new int[l + 1];//存放第一段切割出来的长度
	//初始化价格
	for (int i = 0; i < STEEL_TABLE_SIZE; i++)
		max_cut_price[i] = -1;
	max_cut_price[0] = 0;
	//初始化第一段长度
	for (int i = 0; i < STEEL_TABLE_SIZE; i++)
		first_section[i] = 0;
	for (int i = 1; i <= l; i++) {//在求max_cut_price[i]
		for (int j = 1;j<i ; j++) {//先判断是否需要切割
			int s = max_cut_price[j] + max_cut_price[i - j] - c;
			if (s > max_cut_price[i]) {//如果比当前的解更优,则更新
				max_cut_price[i] = s;
				first_section[i] = j;
			}
		}
		//在判断不需要切割的情况
		if (i <= STEEL_TABLE_SIZE - 1) {//则可能不需要切割
			int s = steel_price[i];
			if (s > max_cut_price[i]) {//如果比当前的解更优,则更新
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
	int s = get_optical_price(29, 1);//长20的钢筋,每次切割价格为2
	cout << "The optical price is " << s << endl;

	return 0;
}