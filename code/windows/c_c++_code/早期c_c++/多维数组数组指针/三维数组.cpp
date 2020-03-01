#include<stdio.h>


void main()
{
	int a[3][4][5];
	int(*px)[4][5] = a;//px是一个指向一个int二维数组的指针，*px代表这个二维数组第一个元素的地址(第一个元素是一个一维数组)
	int(*px2)[5] = *px;//px2是一个指向int一维数组的指针，*px2代表这个一维数组第一个元素的地址
	int* px3 = *px2;//px3是一个指向int类型的指针
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