#include "common.h"

#define N 5

//�жϴ�x�Ƿ��������Ҫ��(����̰���㷨��n��items��ѡȡk��)
bool OK(pair<int, int>* in_items, int n, int k,double x) {
	//������v(i)-x*w(i)�Ĵ�С����
	sort(in_items, in_items + n, [x](pair<int,int> a,pair<int,int> b)->bool {
		return (a.second - x * a.first) > (b.second - x * b.first);
	});
	double sum = 0;
	//�������,ȡ��ǰk��,�����Ƿ�����Ҫ��
	for (int i = 0; i < k; i++)
		sum += in_items[i].second - x * in_items[i].first;
	return sum >= 0;
}

//����n����Ʒ��items������ѡ��k����Ʒ,ʹ��ƽ��ֵ���,�������ƽ��ֵ
double max_average(std::pair<int, int> items[],int n,int k) {
	std::pair<int, int>* in_items = new std::pair<int, int>[n];//�����ڲ�ʹ�õ�����,��Ϊ���ܸ���ԭ����
	for (int i = 0; i < n; i++)//���и���
		in_items[i] = items[i];
	//���������������������,��ȡ��x_max,x_min
	std::sort(in_items, in_items + n, [](std::pair<int,int> a,std::pair<int,int> b)->bool {
		return (a.second / (double)(a.first)) < (b.second / (double)(b.first));
	});
	//����100�ζ��ֲ���
	double x_max = in_items[n - 1].second/(double)(in_items[n-1].first);
	double x_min = in_items[0].second / (double)(in_items[0].first);
	double x_mid;
	for (int i = 0; i < 100; i++) {
		x_mid = (x_max + x_min) / 2;
		if (OK(in_items, n, k, x_mid))
			x_min = x_mid;
		else
			x_max = x_mid;
	}
#ifdef _DEBUG
	cout << "select such items:" << endl;
	for (int i = 0; i < k; i++)
		cout << "weight :" << in_items[i].first << ",value :" << in_items[i].second << endl;
#endif // _DEBUG

	return x_mid;
}

int main3_1_4() {
	int k = 2;//ѡȡ3��,ʹ��ƽ��ֵ���
	//pair.first��ʾweight,pair.second��ʾvalue
	std::pair<int, int> items[] = { {2,3},{2,1},{5,3},{2,1},{3,2} };
	// x = ��v(i)/��w(i),����ʹ�æ�v(i) - ��w(i)*x>=0����x,���Կ��Զ�v(i)-x*w(i)����̰�ĵ�ѡ��

	cout << "average is " << max_average(items, N, k) << endl;

	return 0;
}