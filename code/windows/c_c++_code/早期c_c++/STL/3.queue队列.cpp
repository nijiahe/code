#include<iostream>
#include<queue>

using namespace std;

/*�Ŷ�ʽ�洢��ʽ*/
void main30()
{
	queue<int>myqueue;
	myqueue.push(1);
	myqueue.push(2);
	myqueue.push(3);
	myqueue.push(4);
	/*myqueue.back�������β,myqueue.front���������ǰ��*/
	while (!myqueue.empty())
	{
		cout << myqueue.front() << endl;
		myqueue.pop();
	}
	cin.get();
}