#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() 
{
	int a=0,b=0;
	printf("请输入迷宫规格\n");
	while (1)
	{
		a = 0;
		printf("长:");
		scanf_s("%d", &a);
		if ((a-2) % 3 == 0 && a > 6&&a<=99) break;
		else
		{
			printf("重新输入\n");
			continue;
		}
	}
	while (1)
	{
			b = 0;
			printf("宽:");
			scanf_s("%d", &b);
			if ((b-2) % 3 == 0 && b > 6 && b <= 99) break;
			else
			{
				printf("重新输入\n");
				continue;
			}
	}
	int mg[99][99] = { 0 };
	srand(time(NULL));
	for (int i = 0;i < a;i++)
	{
		for (int j = 0;j < b;j++)
		{
			if (i == 0 || j == 0 || i == a - 1 || j == b - 1)mg[i][j] = 1;
			if (i % 2 == 0 && j % 2 == 0&&i!=0&&j!=0&&i!=a-1&&j!=b-1)
			{
				mg[i][j] = 1;
				
				int s = rand() % 4 + 1;
				switch (s)
				{
				case (1):
					mg[i][j - 1] = 1;
					break;
				case (2):
					mg[i][j + 1] = 1;
					break;
				case (3):
					mg[i - 1][j] = 1;
					break;
				case (4):
					mg[i + 1][j] = 1;
					break;
				default:
					break;
				}
			}
		}
	}
	for (int i = 0;i < a;i++)
	{
		for (int j = 0;j < b;j++)
		{
			if (mg[i][j] == 1 && j < b - 1)printf("* ");
			else if (j == b - 1)printf("* \n");
			else printf("  ");
		}
	}
 }