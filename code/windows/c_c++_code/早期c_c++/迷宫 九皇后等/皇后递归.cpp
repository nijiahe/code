/*#include<iostream>

using namespace std;

#define queendiguisidelength 5


class Queen
{
public:
	int queen[queendiguisidelength][queendiguisidelength] = { 0 };
	bool seatok(int x,int y)//判断这个地方放棋子是否Ok
	{//将放置了棋子的地方标记为1
		for (int i = 0; i < x; i++)
		{
			if (queen[i][y] == 1)//如果这一行之前的地方有棋子
			{
				return 0;
			}
		}
		for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)//左上之前的地方有棋子
		{
			if (queen[i][j] == 1)
			{
				return 0;
			}
		}
		for (int i = x - 1, j = y + 1; i >= 0 && j < queendiguisidelength; i--, j++)//左下之前的地方有棋子
		{
			if (queen[i][j] == 1)
			{
				return 0;
			}
		}
		return 1;
	}
	int calculateway(int x = 0)//从queen数组[0][0]处开始依次
	{
		int res = 0;
		if (x == queendiguisidelength - 1 )
		{
			for (int i = 0; i < queendiguisidelength; i++)
			{
				if (seatok(x, i))
				{
					queen[x][i] = 1;
					res++;
					showqueen();
					queen[x][i] = 0;
				}
			}
		}
		else 
		for (int i = 0; i < queendiguisidelength; i++)
		{
			if (seatok(x, i))
			{
				queen[x][i] = 1;
				res += calculateway(x + 1);
				queen[x][i] = 0;
			}
		}
		return res;
	}
	void showqueen()
	{
		cout << "----------------" << endl;
		for (int i = 0; i < queendiguisidelength; i++)
		{
			cout << "|";
			for (int j = 0; j < queendiguisidelength; j++)
			{
				if (queen[i][j] == 0)
				{
					cout << "  ";
				}
				if (queen[i][j] == 1)
				{
					cout << "* ";
				}
			}
			cout << "|";
			cout << endl;
		}
		cout << "----------------" << endl;
	}
};



void mainC()
{
	Queen queen1;
	cout << queen1.calculateway() << endl;
	cout << "queen1" << endl;
	cin.get();
}*/