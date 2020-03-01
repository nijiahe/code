#include<iostream>
#include<set>
#include<bitset>

using namespace std;

void main120()
{	
	int num = 255;
	bitset<8>bs(num);/*8代表8个二进制位,255代表要转换的数*/
	bs.set(1, 0);/*操作二进制位*/
	cout << "数字" << num << "二进制位大小" << bs.size() << endl;
	for (int i = 7; i >= 0; i--)
	{
		cout << bs[i];
	}
	
	cin.get();
}