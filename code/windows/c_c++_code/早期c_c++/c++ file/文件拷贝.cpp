#include<iostream>
#include<fstream>/*�ļ���ָ��ͷ�ļ�*/
/*��F:\\3.txt������F:\\1.txt*/
using namespace std;

void maincopy()
{
	ifstream input("F:\\3.txt", ios::in);
	ofstream output("F:\\1.txt", ios::out);
	if (!input || !output)/*���input����һ���ļ�ָ�����output����һ���ļ�ָ��*/
	{
		cout << "�ļ�ָ�봴��ʧ��" << endl;
		cin.get();
		return;
	}
	cout << "��ʼ����" << endl;
	char ch;
	while (input.get(ch))/*��input��ȡ��charʱ*/
	{
		output.put(ch);/*���ch��output�򿪵��ļ�*/
	}
	cout << "�������" << endl;
	input.close();
	output.close();

	cin.get();
}