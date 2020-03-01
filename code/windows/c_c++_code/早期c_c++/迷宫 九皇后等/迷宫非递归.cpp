/*#include <stdio.h>
#include <stdlib.h>

#define COUNT_I 9
#define COUNT_J 8
#define START_I 0
#define START_J 0
#define END_I 8
#define END_J 7
#define MAXSIZE 1000

//����λ�ýṹ��
typedef struct local {

	int x;
	int y;

}LOCAL;

//ջ�ṹ
typedef struct stack {

	LOCAL data[MAXSIZE];//ջ�������һ������λ������
	int top;

}STACK;

//��ʼ��ջ
STACK *InitStack(void)//�ڶ��Ͻ���һ��ջ����ջ�м�¼Ԫ��������int������ʼ��Ϊ-1,�������ջ��ָ��
{
	STACK *maze;
	maze = (STACK *)malloc(sizeof(STACK));
	maze->top = -1;

	return maze;
}

//��ջ��
int EmptyStack(STACK *maze)
{
	if (maze->top == -1)
		return 1;
	else
		return 0;
}

//��ջ��
int IsFull(STACK *maze)
{
	if (maze->top == MAXSIZE - 1)
		return 1;
	else
		return 0;

}

//��ջ
int PushStack(STACK *maze, LOCAL *x)
{
	if (maze->top <= MAXSIZE - 1) {
		maze->data[++maze->top] = *x;
		return 1;
	}
	else {
		printf("ջ����\n");
		return 0;
	}
}

//��ջ
int PopStack(STACK *maze, LOCAL *x)
{
	if (maze->top > -1) {
		*x = maze->data[maze->top];
		maze->top--;
		return 1;
	}
	else {
		printf("ջ�ѿ�\n");
		return 0;
	}
}

//���Թ�����
int VistMaze(int maze[][COUNT_J], LOCAL path[][COUNT_J])
{
	int i, j;

	//��ʼ��ջ
	STACK *stack;
	LOCAL temp;
	stack = InitStack();
	temp.x = 0; temp.y = 0;
	if (maze[START_I][START_J] == 0)
		PushStack(stack, &temp);
	else
		return 0;
	while (!EmptyStack(stack)) 
	{
		PopStack(stack, &temp);
		i = temp.x;	j = temp.y;
		maze[i][j] = 2;

		if (i == END_I && j == END_J)
			break;

		//��
		if (i + 1 <= END_I && maze[i + 1][j] == 0) {
			maze[i + 1][j] = 2;
			path[i + 1][j].x = i;	path[i + 1][j].y = j;
			temp.x = i + 1;
			temp.y = j;
			PushStack(stack, &temp);
		}
		//��
		if (j + 1 <= END_J && maze[i][j + 1] == 0) {
			maze[i][j + 1] = 2;
			path[i][j + 1].x = i;	path[i][j + 1].y = j;
			temp.x = i;
			temp.y = j + 1;
			PushStack(stack, &temp);
		}
		//��
		if (j - 1 >= 0 && maze[i][j - 1] == 0) {
			maze[i][j - 1] = 2;
			path[i][j - 1].x = i;	path[i][j - 1].y = j;
			temp.x = i;
			temp.y = j - 1;
			PushStack(stack, &temp);
		}
		//��
		if (i - 1 >= 0 && maze[i - 1][j] == 0) {
			maze[i - 1][j] = 2;
			path[i - 1][j].x = i;	path[i - 1][j].y = j;
			temp.x = i - 1;
			temp.y = j;
			PushStack(stack, &temp);
		}
	}
	//��������յ���˳���ѭ����·����ʶ����
	if (i == END_I && j == END_J) {
		maze[i][j] = 3;
		while (path[temp.x][temp.y].x != -1) {
			temp = path[temp.x][temp.y];
			maze[temp.x][temp.y] = 3;
		}

		return 1;
	}
	else {
		return 0;
	}
}



int mainB(void)
{
	//�Թ�
	int i, j;
	int maze[COUNT_I][COUNT_J] = {
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

	//����·������,����(x,y)���·�����������
	LOCAL path[COUNT_I][COUNT_J];
	for (i = 0; i < COUNT_I; i++) {
		for (j = 0; j < COUNT_J; j++) {
			path[i][j].x = -1;
			path[i][j].y = -1;
		}
	}

	//��ӡ���Թ�
	printf("ԭ�Թ���\n");
	for (i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < COUNT_I; i++) {
		printf("|");
		for (j = 0; j < COUNT_J; j++) {
			if (maze[i][j] == 1)
				printf("@");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for (i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");

	if (VistMaze(maze, path) == 0) {
		printf("û��·������\n");
		exit(0);
	}

	//��ӡ���Թ���·��
	printf("�Թ���·����\n");
	for (i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < COUNT_I; i++) {
		printf("|");
		for (j = 0; j < COUNT_J; j++) {
			if (maze[i][j] == 1)
				printf("@");
			else if (maze[i][j] == 3)
				printf("%%");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for (i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");

	return 0;
}*/


#include<iostream>
#include<cstdlib>

using namespace std;

static const int mymazelongsize = 10;
static const int mymazewidesize = 10;

struct	position
{
	int x;
	int y;
	position()
	{

	}
	position(int x,int y):x(x),y(y)
	{

	}
};

struct positionarray
{
	position positions[mymazelongsize*mymazewidesize];
	int elemnum = -1;
	void addelem(position place)
	{
		positions[elemnum + 1] = place;
		elemnum++;
	}
	void addelem(int x,int y)
	{
		position place1(x, y);
		positions[elemnum + 1] = place1;
		elemnum++;
	}
	position popelem()
	{
		if (elemnum > -1)
		{
			return positions[elemnum--];
		}
		else
		{
			exit(0);
		}
	}
	bool ifempty()
	{
		if (elemnum == -1)
		{
			return 1;
		}
		else if (elemnum >= 0)
		{
			return 0;
		}
		else
		{
			exit(0);
		}
	}
	position operator [](int index)
	{
		return positions[index];
	}
};


class Maze2
{
public:
	int thismaze[mymazelongsize][mymazewidesize];
	positionarray place;
	Maze2()
	{

	}
	~Maze2()
	{
		delete[] thismaze;
	}
	Maze2(int zmaze[mymazelongsize][mymazewidesize])
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
		if (y < mymazewidesize - 1 && thismaze[x][y + 1] == 0)
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
		if (x < mymazelongsize - 1 && thismaze[x + 1][y] == 0)
		{
			return 1;
		}
		return 0;
	}
	//0 ·  1ǽ  2���Թ�·��  3 
	int walk(int x, int y)//���Թ����ұ���Թ�
	{
		int end = 0;
		this->thismaze[x][y] = 2;//���߹��ĵط����Ϊ2
		position pos(x, y);//pos λ��
		place.addelem(pos);
		while (!place.ifempty())//place λ������
		{
			//3����̽�������߲�ͨ��
			int newway = 0;
			pos = place[place.elemnum];
			thismaze[pos.x][pos.y] = 2;
			if (place[place.elemnum].x == mymazelongsize - 1 && place[place.elemnum].y == mymazewidesize - 1)//����Ѿ��ߵ����յ�
			{
				thismaze[place[place.elemnum].x][place[place.elemnum].y] = 2;
				end = 1;//��end���Ϊ1
				break;
			}
			if (end != 1 && downroad(pos.x, pos.y)&&thismaze[pos.x][pos.y + 1]!=3)//���������·
			{
				place.addelem(pos.x, pos.y + 1);
				newway++;
			}
			if (end != 1 && rightroad(pos.x, pos.y) && thismaze[pos.x + 1][pos.y] != 3)//����ұ���·
			{
				place.addelem(pos.x + 1, pos.y);
				newway++;
			}
			if (end != 1 && leftroad(pos.x, pos.y) && thismaze[pos.x - 1][pos.y] != 3)//��������·
			{
				place.addelem(pos.x - 1, pos.y);
				newway++;
			}
			if (end != 1 && uproad(pos.x, pos.y) && thismaze[pos.x][pos.y - 1] != 3)//���������·
			{
				place.addelem(pos.x, pos.y - 1);
				newway++;
			}
			if(newway==0)
			{
				thismaze[place[place.elemnum].x][place[place.elemnum].y] = 3;
				place.popelem();
			}
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
				if (this->thismaze[i][j] == 3)//�߹���·
				{
					cout << ' ';
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
		int res = this->walk(0, 0);
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


void mainD()
{
	int maze[mymazelongsize][mymazewidesize] = {
		{ 0,0,1,0,0,0,1,0,1,0 },
		{ 0,1,1,0,0,0,1,0,1,0 },
		{ 0,0,0,0,1,1,0,1,0,1 },
		{ 0,1,1,0,0,0,1,0,0,1 },
		{ 0,0,0,1,0,0,0,0,1,0 },
		{ 0,1,0,0,0,1,1,1,1,1 },
		{ 0,1,0,1,1,0,0,1,0,1 },
		{ 1,1,0,0,1,1,0,1,1,0 },
		{ 1,1,0,0,0,0,0,0,0,0 },
		{ 1,0,1,1,0,0,1,0,1,0, },
	};
	Maze2 maze2(maze);
	maze2.autoshow();
	cin.get();
}