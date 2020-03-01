#include <iostream>
#include <cstdlib>

static int N = 200;

using namespace std;

/*
ʱ�临�Ӷȷ�����
��n=0��n=1ʱΪO(1)
��T(0)=T(1)=1;
T(n)=T(n-1)+T(n-2)+1,��ΪҪ����һ�μӷ�
������ѧ���������֪ʶ����S(n)=(T(n)+1)/2,��S(0)=1,S(1)=1,S(n)=(T(n-1)+T(n-2)+2)/2=S(n-1)+S(n-2),Ҳ��һ��쳲��������У�
��T(n)=2S(n)-1ΪO(ָ������
*//*����ͨ�ĵݹ��㷨*/
_int64 Fibonacci1(int n) {
	return n < 2 ? n : Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

/*���䷨����¼ǰ�����������һ�������Եݹ�*/
_int64 Fibonacci2(int n, _int64 &prev) {
	if (n == 0) { prev = 1; return 0; }
	else {
		_int64 prevPrev;
		prev = Fibonacci2(n - 1, prevPrev);
		return prev + prevPrev;
	}
}

/*���¶��ϣ���̬�滮*/
_int64 Fibonacci3(int n) {
	int i = 0, lef = 0, rig = 1;
	while (i++ < n) {
		rig = lef + rig;
		lef = rig - lef;
	}
	return lef + rig;
}

int main1_452()
{
	_int64 num;
	for (int i = 1; i < N; i++)
		cout << "Fibonacci(" << i << ")" << Fibonacci2(i,num) << endl;


	system("pause");
	return 0;
}