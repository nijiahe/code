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
	bool seatok(int x, int y)//�ж�����ط��������Ƿ�Ok
	{//�����������ӵĵط����Ϊ1
		for (int i = 0; i < x; i++)
		{
			if (queen[i][y] == 1)//�����һ��֮ǰ�ĵط�������
			{
				return 0;
			}
		}
		for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)//����֮ǰ�ĵط�������
		{
			if (queen[i][j] == 1)
			{
				return 0;
			}
		}
		for (int i = x - 1, j = y + 1; i >= 0 && j < queenfeidiguisidelength; i--, j++)//����֮ǰ�ĵط�������
		{
			if (queen[i][j] == 1)
			{
				return 0;
			}
		}
		return 1;
	}
	int calculateway(int x = 0)//��queen����[0][0]����ʼ����
	{
		int res = 0;
		for (int i = 0; i < queenfeidiguisidelength; i++)
		{
			thisarray.inputseat(0, i);
		}
		while (!thisarray.ifempty())
		{
			int nowSeatOKnum = 0;
			seat queentop = thisarray[thisarray.elemnum];//��¼��ǰ����
			if (queen[queentop.x][queentop.y] == 1)//����������Ѿ��������ӵĵط�,�ٴ�ѭ��������˵��������ܵ��������֤ʵ��������,������ȡ��,������
			{
				queen[queentop.x][queentop.y] = 0;
				thisarray.popseat();
				continue;
			}
			queen[queentop.x][queentop.y] = 1;//��ϵ�Ԫ���������еĵط���Ϊ1,���������������
			if (queentop.x == queenfeidiguisidelength - 1)//����������һ��,ֱ��չʾ,֮��ȡ������,�������Ԫ��,����ѭ��ͷ
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
					nowSeatOKnum++;//��ǰ���ԷŽ�ȥ��Ԫ��
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