#include<iostream>
#include<set>
#include<bitset>

using namespace std;

void main120()
{	
	int num = 255;
	bitset<8>bs(num);/*8����8��������λ,255����Ҫת������*/
	bs.set(1, 0);/*����������λ*/
	cout << "����" << num << "������λ��С" << bs.size() << endl;
	for (int i = 7; i >= 0; i--)
	{
		cout << bs[i];
	}
	
	cin.get();
}