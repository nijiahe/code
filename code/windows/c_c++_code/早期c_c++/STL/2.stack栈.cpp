#include<iostream>
#include<stack>

using namespace std;
/*�����жѷ�Ԫ��ʽ�洢��ʽ*/
void main20()
{
	int num;
	cin >> num;
	stack<int> mystack;/*����һ���洢int���͵�ջ*/
	for (; num; num /= 2)
	{
		mystack.push(num % 2);/*��num�Ķ���������ѹ��ջ*/
	}
	cout << "ջԪ�ش�С" << mystack.size() << endl;
	while (!mystack.empty())/*��ջ��Ϊ��ʱ*/
	{
		cout << mystack.top() << " ";/*��ȡջ�����ֵ*/
		mystack.pop();/*����ջ���Ԫ��*/
		/*mystack.pop()����ֵΪvoid,���ý�Ϊ����ջ���˵�Ԫ��*/
	}
	cin.get();
	cin.get();
}