#include<iostream>
#include<string>

using namespace std;
/*erase������ԭ�����£�
��1��string& erase(size_t pos = 0, size_t n = npos);
��2��iterator erase(iterator position);
��3��iterator erase(iterator first, iterator last);
Ҳ����˵�������÷���
��1��erase(pos, n); ɾ����pos��ʼ��n���ַ�������erase(0, 1)����ɾ����һ���ַ�
��2��erase(position); ɾ��position����һ���ַ�(position�Ǹ�string���͵ĵ�����)
��3��erase(first, last); ɾ����first��last֮����ַ���first��last���ǵ�������*/
void main130()
{
	//char str[] = "asdfg";
	string str("abcdefghijki");
	str.insert(str.begin(), 3, 'z');/*��һ��λ�ò���3��z*/
	str.erase(str.begin());/*ɾ��*/
	str.replace(5, 0, "xxx");/*�����λ��,����ʱɾ���ĳ���,Ҫ������ַ���*/
	cout << str << endl;
	cout << "********************" << endl;
	int pos1 = str.find("ijk");
	cout << pos1 << endl;/*find�ҵ���������ַ���������Ŀ�ͷλ��str[i],ʧ�ܷ���-1*/
	int pos2 = str.find_last_of("i");/*���һ��ƥ���λ��*/
	cout << pos2 << endl;
	int pos3 = str.find('i', pos1+1);/*ָ��find���ַ����ĵڼ���Ԫ�ؽ��в���*/
	cout << pos3 << endl;
	cin.get();
}