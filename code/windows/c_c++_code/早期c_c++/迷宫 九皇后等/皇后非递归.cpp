#include<iostream>

using namespace std;

const int queenfeidiguisidelength = 8;

struct seat
{
	int x;
	int y;
	seat()
	{

	}
	seat(int x,int y) :x(x), y(y)
	{

	}
};

struct queenarray
{
	seat queenseat[queenfeidiguisidelength*queenfeidiguisidelength];
	int elemnum = -1;
	void inputseat(seat value)
	{
		queenseat[elemnum + 1] = value;
		elemnum++;
	}
	void inputseat(int x,int y)
	{
		queenseat[elemnum + 1].x = x;
		queenseat[elemnum + 1].y = y;
		elemnum++;
	}
	void popseat()
	{
		elemnum--;
	}
	bool ifempty()
	{
		if (elemnum == -1)
		{
			return 1;
		}
		return 0;
	}
	seat operator[](int index)
	{
		return queenseat[index];
	}
};


class Queen
{
public:
	int queen[queenfeidiguisidelength][queenfeidiguisidelength] = { 0 };
	queenarray thisarray;
	bool seatok(int x, int y)//判断这个地方放棋子是否Ok
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
		for (int i = x - 1, j = y + 1; i >= 0 && j < queenfeidiguisidelength; i--, j++)//左下之前的地方有棋子
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
		for (int i = 0; i < queenfeidiguisidelength; i++)
		{
			thisarray.inputseat(0, i);
		}
		while (!thisarray.ifempty())
		{
			int nowSeatOKnum = 0;
			seat queentop = thisarray[thisarray.elemnum];//记录当前顶端
			if (queen[queentop.x][queentop.y] == 1)//如果这里是已经放了棋子的地方,再次循环到这里说明这里可能的情况都被证实不存在了,把棋子取出,弹出他
			{
				queen[queentop.x][queentop.y] = 0;
				thisarray.popseat();
				continue;
			}
			queen[queentop.x][queentop.y] = 1;//最顶上的元素在棋盘中的地方设为1,代表这里存在棋子
			if (queentop.x == queenfeidiguisidelength - 1)//如果顶是最后一列,直接展示,之后取出棋子,弹出这个元素,返回循环头
			{
				this->showqueen();
				res++;
				queen[queentop.x][queentop.y] = 0;
				thisarray.popseat();
				continue;
			}
			for (int i = 0; i < queenfeidiguisidelength; i++)
			{
				if (seatok(queentop.x+1, i))
				{
					thisarray.inputseat(queentop.x + 1, i);
					nowSeatOKnum++;//当前可以放进去的元素
				}
			}
			if (nowSeatOKnum == 0)
			{
				queen[queentop.x][queentop.y] = 0;
				thisarray.popseat();
			}
		}		
		return res;
	}

	void showqueen()
	{
		cout << "----------------" << endl;
		for (int i = 0; i < queenfeidiguisidelength; i++)
		{
			cout << "|";
			for (int j = 0; j < queenfeidiguisidelength; j++)
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



void main()
{
	Queen queen2;
	cout << queen2.calculateway() << endl;

	cin.get();
}