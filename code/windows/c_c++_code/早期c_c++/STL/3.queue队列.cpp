#include<iostream>
#include<queue>

using namespace std;

/*排队式存储方式*/
void main30()
{
	queue<int>myqueue;
	myqueue.push(1);
	myqueue.push(2);
	myqueue.push(3);
	myqueue.push(4);
	/*myqueue.back代表队伍尾,myqueue.front代表队伍最前端*/
	while (!myqueue.empty())
	{
		cout << myqueue.front() << endl;
		myqueue.pop();
	}
	cin.get();
}