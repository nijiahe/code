#include "common.h"

//O(nk)�����㷽��,ʹ�ҵ���Ǯ������С,��̬�滮
/*
˼����ʽ:�ñ�񷨼�¼ǰi-1��Ԫ�ص�������㷽��,i��������㷽��ֻ������1+min{ i-K[j]},���ٶ��˴������а���һ����ֵ,�ҳ�ȥ�������ֵ�����Сֵ
ÿ��Ԫ�ػ�O(k)��ʱ��,��O(nk),�ռ临�Ӷ�O(n)
*/

//������ֵ����Money,�����Сs,���бذ�����ֵΪ1��Ӳ��,��Ӧ���κ��������,��n�����㷽ʽ,��̬�滮
int change(int* Money, int s, int n) {
	int* nums = new int[n + 1];
	for (int i = 0; i <= n; i++)nums[i] = INT_MAX;//��ʼ��
	nums[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < s; j++) {//������ֵ����
			if (Money[j] <= i) {//�����������ֵ��Ӳ�����ָ��������,����ǰҪ��������ֵ�ȴ���ֵ��
				int n = 1 + nums[i - Money[j]];
				if (nums[i] > n)
					nums[i] = n;
			}
		}
	}

#ifdef _DEBUG
	cout << "start log nums" << endl;
	cout << setw(7) << "money";
	for (int i = 0; i <= n; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << setw(7) << "num";
	for (int i = 0; i <= n; i++)
		cout << setw(3) << nums[i];
	cout << endl;
#endif

	int val = nums[n];
	delete[]nums;
	return val;
}


int mains16_1() {
	int Money[6] = { 11,9,5,4,3,1 };
	int n = change(Money, 6, 36);

	return 0;
}