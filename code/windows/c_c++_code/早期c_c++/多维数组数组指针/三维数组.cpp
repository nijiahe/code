#include<stdio.h>


void main()
{
	int a[3][4][5];
	int(*px)[4][5] = a;//px��һ��ָ��һ��int��ά�����ָ�룬*px���������ά�����һ��Ԫ�صĵ�ַ(��һ��Ԫ����һ��һά����)
	int(*px2)[5] = *px;//px2��һ��ָ��intһά�����ָ�룬*px2�������һά�����һ��Ԫ�صĵ�ַ
	int* px3 = *px2;//px3��һ��ָ��int���͵�ָ��
	for (int *ptr = px3,i=0; ptr < px3 + 60; ptr++,i++)
	{
		*ptr = i;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 5; k++)
			{
				printf("%d ", a[i][j][k]);
			}
			printf("\n");
		}
		printf("\n\n\n");
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				printf("%d ", px[i][j][k]);
			}
			printf("\n");
		}
		printf("\n\n\n");
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				printf("%d ", (*(px+i))[j][k]);
			}
			printf("\n");
		}
		printf("\n\n\n");
	}

	getchar();

}