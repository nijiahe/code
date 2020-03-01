/*#include <stdio.h>
#include <stdlib.h>



#define END_I 8
#define END_J 7
#define START_I 0
#define START_J 0

//���Թ�
int VistMaze(int maze[][8], int i, int j)
{
	int end = 0;

	//�����ܹ���ͨ
	maze[i][j] = 2;

	//��������ص���end��Ϊ0��ʾ�Թ��Ѿ��߽���
	if (i == END_I && j == END_J) {
		end = 1;
	}
	//����Թ�û���߽�������������λ�õ��ҡ��¡������ĸ������Ƿ��ܹ���ͨ
	if (end != 1 && j + 1 <= END_J && maze[i][j + 1] == 0) {		//��
		if (VistMaze(maze, i, j + 1) == 1)
			return 1;
	}
	if (end != 1 && i + 1 <= END_I && maze[i + 1][j] == 0) {		//��
		if (VistMaze(maze, i + 1, j) == 1)
			return 1;
	}
	if (end != 1 && j - 1 >= START_J && maze[i][j - 1] == 0) {	//��
		if (VistMaze(maze, i, j - 1) == 1)
			return 1;
	}
	if (end != 1 && i - 1 >= START_I && maze[i - 1][j] == 0) {	//��
		if (VistMaze(maze, i - 1, j) == 1)
			return 1;
	}	//�����ܶ���ͨ��ʱ�����û�0
	if (end != 1) {
		maze[i][j] = 0;
	}

	return end;
}

int mainA(void)
{
	//�Թ�
	int i, j;
	int maze[9][8] = {
		{ 0,0,1,0,0,0,1,0 },
		{ 0,0,1,0,0,0,1,0 },
		{ 0,0,0,0,1,1,0,1 },
		{ 0,1,1,1,0,0,1,0 },
		{ 0,0,0,1,0,0,0,0 },
		{ 0,1,0,0,0,1,0,1 },
		{ 0,1,1,1,1,0,0,1 },
		{ 1,1,0,0,1,1,0,1 },
		{ 1,1,0,0,0,0,0,0 }
	};
	//��ӡ���Թ�
	printf("ԭ�Թ���\n");
	for (i = 0; i <= 9; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < 9; i++) {
		printf("|");
		for (j = 0; j < 8; j++) {
			if (maze[i][j] == 1)
				printf("@");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for (i = 0; i <= 9; i++)
		printf("-");
	printf("\n");

	if (VistMaze(maze, 0, 0) == 0) {
		printf("û��·������\n");
		exit(0);
	}

	//��ӡ���Թ���·��
	printf("�Թ���·����\n");
	for (i = 0; i <= 9; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < 9; i++) {
		printf("|");
		for (j = 0; j < 8; j++) {
			if (maze[i][j] == 1)
				printf("@");
			else if (maze[i][j] == 2)
				printf("%%");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for (i = 0; i <= 9; i++)
		printf("-");
	printf("\n");

	system("pause");
	return 0;
}*/
/*
#include<iostream>
#include<cstdlib>

using namespace std;

static const int mymazelongsize = 10;
static const int mymazewidesize = 10;

class Maze1
{
public:
	int thismaze[mymazelongsize][mymazewidesize];
	Maze1()
	{

	}
	~Maze1()
	{
		delete []thismaze;
	}
	Maze1(int zmaze[mymazelongsize][mymazewidesize])
	{
		for (int i = 0; i < mymazelongsize; i++)
		{
			for (int j = 0; j < mymazewidesize; j++)
			{
				thismaze[i][j] = zmaze[i][j];
			}
		}
	}
	bool uproad(int x, int y)
	{
		if (y > 0 && thismaze[x][y - 1] == 0)
		{
			return 1;
		}
		return 0;
	}
	bool downroad(int x, int y)
	{
		if (y < mymazewidesize-1 && thismaze[x][y + 1] == 0)
		{
			return 1;
		}
		return 0;
	}
	bool leftroad(int x, int y)
	{
		if (x > 0 && thismaze[x - 1][y] == 0)
		{
			return 1;
		}
		return 0;
	}
	bool rightroad(int x, int y)
	{
		if (x < mymazelongsize-1 && thismaze[x + 1][y] == 0)
		{
			return 1;
		}
		return 0;
	}
	int walk(int x,int y)//���Թ����ұ���Թ�
	{
		int end = 0;
		this->thismaze[x][y] = 2;//���߹��ĵط����Ϊ2
		if (x == mymazelongsize - 1 && y == mymazewidesize - 1)//����Ѿ��ߵ����յ�
		{
			end = 1;//��end���Ϊ1
		}
		if (end != 1 && downroad(x, y))//���������·
		{
			if (walk(x, y + 1) == 1)
			{
				return 1;
			}
		}
		if (end != 1 && rightroad(x, y))//����ұ���·
		{
			if (walk(x + 1, y) == 1)
			{
				return 1;
			}
		}
		if (end != 1 && leftroad(x, y))//��������·
		{
			if (walk(x -1, y) == 1)
			{
				return 1;
			}
		}
		if (end != 1 && uproad(x, y))//��������·
		{
			if (walk(x, y - 1) == 1)
			{
				return 1;
			}
		}
		if (end != 1)
		{
			this->thismaze[x][y] = 0;
		}
		return end;
	}
	void showmaze()
	{
		cout << "-----------------------" << endl;
		for (int i = 0; i < mymazelongsize; i++)
		{
			cout << "|";
			for (int j = 0; j < mymazewidesize; j++)
			{				
				if (this->thismaze[i][j] == 0)//·
				{
					cout << ' ';
				}
				if (this->thismaze[i][j] == 1)//ǽ
				{
					cout << 'O';
				}
				if (this->thismaze[i][j] == 2)//�߹���·
				{
					cout << '*';
				}
			}
			cout << "|";
			cout << endl;
		}
		cout << "-----------------------" << endl;
	}
	void autoshow()
	{
		cout << "ԭ�Թ�:" << endl;
		this->showmaze();
		if (this->thismaze[0][0] != 0)
		{
			cout << "�Թ�[0][0]����Ϊ0" << endl;
			return;
		}
		int res = this->walk(0,0);
		if (res == 0)
		{
			cout << "��·��" << endl;
		}
		else if (res == 1)
		{
			cout << "�Թ�·��" << endl;
			this->showmaze();
		}
		else
		{
			cout << "error" << endl;
		}
	}
};


void mainA()
{
	int maze[mymazelongsize][mymazewidesize] = {
		{ 0,0,1,0,0,0,1,0,1,0 },
		{ 0,0,1,0,0,0,1,0,1,0 },
		{ 0,0,0,1,1,1,0,1,0,1 },
		{ 0,1,1,0,0,0,1,0,0,1 },
		{ 0,0,0,1,0,0,0,0,1,0 },
		{ 0,1,0,0,0,1,0,1,1,1 },
		{ 0,1,1,1,1,0,0,1,0,1 },
		{ 1,1,0,0,1,1,0,1,1,0 },
		{ 1,1,0,0,0,0,0,0,0,0 },
		{ 1,0,1,1,0,0,1,0,1,0,},
	};
	Maze1 maze1(maze);
	maze1.autoshow();
	cin.get();
}*/