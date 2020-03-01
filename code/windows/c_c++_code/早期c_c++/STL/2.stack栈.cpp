#include<iostream>
#include<stack>

using namespace std;
/*容器中堆放元素式存储方式*/
void main20()
{
	int num;
	cin >> num;
	stack<int> mystack;/*创建一个存储int类型的栈*/
	for (; num; num /= 2)
	{
		mystack.push(num % 2);/*将num的二进制数据压入栈*/
	}
	cout << "栈元素大小" << mystack.size() << endl;
	while (!mystack.empty())/*当栈不为空时*/
	{
		cout << mystack.top() << " ";/*读取栈最顶端数值*/
		mystack.pop();/*弹出栈最顶端元素*/
		/*mystack.pop()返回值为void,作用仅为弹出栈顶端的元素*/
	}
	cin.get();
	cin.get();
}