#include<Windows.h>
#include <stdio.h>
#include <conio.h>
#include <shellapi.h>
#include <time.h>

int size=0,max=0,min=1,score=0;
typedef struct { int x; int y; } DIC;
void menu();
void random(int **p);
void hebin(int** p, char key);
void output(int** p);
void getmax(int** p);
void getmin(int** p);
void restart();

int main()
{
	int *buffer=0;
	int **array=0;
	char move;
	srand((unsigned int)time(NULL));
	menu();
	
	buffer = (int*)malloc(sizeof(int) * size * size);
	array = (int**)malloc(sizeof(int) * 10);
	if (!buffer && !array) printf("内存分配失败") ,exit(0);
	for (int i = 0; i < size; i++)
	{
		array[i] = &buffer[i * size];
	}
	for (int i = 0; i < size; i++)
		for (int j =0; j< size; j++) array[i][j] = 0;
	array[0][0] = 1;
	while (1)
	{
		output(array);
		move = _getch();
		hebin(array, move);
		getmax(array);
		getmin(array);
		random(array);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (array[i][j] >= 2048 || GetAsyncKeyState(VK_MBUTTON)) 
				{ 
					printf("游戏结束\n");
					free(buffer);
					free(array);
					printf("按R重启，按E退出\n");
					while(1)
					{
					if (GetAsyncKeyState('R') ) restart();
					else if ( GetAsyncKeyState('E')) exit(0); 
					Sleep(10);
					}
					
				}
	}

}
void menu()
{
	printf("2048小游戏\n按下空格开始");
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			printf("\n输入网格大小(2<n<11): ");
			while (1)
			{
				scanf_s("%d", &size);
				if (size > 2 && size < 11) break;
				else printf("重新输入: ");
			}
			min = 1, max = 0;
			return;
		}
	}

}
void random(int **p)
{
	while (1)
	{
		int m = rand() % size, n = rand () % (size);
		if (p[m][n] == 0)
		{
			p[m][n] = min>0?min:1;
			return;
		}
	}
}
void hebin(int **p,char key)
{
	int mv = 0,t=0;
	DIC dic = { 0,0 };
	switch (key)
	{
	case 'w':
		printf("↑");
		dic.y = -1;
		break;
	case 's':
		printf("↓");
		dic.y = 1;
		break;
	case 'a':
		printf("←");
		dic.x = -1;
		break;
	case 'd':
		printf("→");
		dic.x = 1;
		break;
	default: printf("输入错误");
		return;
	}
	Sleep(500);
	while (!mv)
	{
		mv = 1;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (j + dic.x >= 0 && j + dic.x < size && i + dic.y >= 0 && i + dic.y < size)
				{
					if (p[i+dic.y][j + dic.x] < p[i][j])
					{
						t = p[i + dic.y][j + dic.x];
						p[i+dic.y][j + dic.x] = p[i][j];
						p[i][j] =t;
						mv=0;
					}
					else if (p[i+dic.y][j + dic.x] == p[i][j]&&p[i][j])
					{
						score += p[i][j];
						p[i+dic.y][j + dic.x] *= 2;
						p[i][j] = 0;
						mv = 0;
					}
				
				}
			}
		}
	}

}
void output(int** p)
{
	system("cls");
	printf("游戏开始(%d*%d)\n", size, size);
	printf("按WASD进行操作 ←→↑↓\n按 W|A|S|D+中键 放弃\n");
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
		{
			if (p[i][j] > 0)printf("%4d|", p[i][j]);
			else printf("    |");
		}
		printf("\n");
	}
	printf("得分: %d\n最小附加数:%d\n",score,min);
}
void getmax(int** p)
{
	max = p[0][0];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (max < p[i][j]) max = p[i][j];
		}
}
void getmin(int** p)
{
	min = 2048;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (p[i][j]&&min > p[i][j]) min = p[i][j];
		}
}
void restart()
{
	//获取当前路径
	wchar_t path[128];
	DWORD result = GetModuleFileName(NULL, path, 128);
	if (result < 1) {
		printf("获取当前路径失败\n");
		return;
	}

	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = L"open";
	sei.lpFile = path;
	sei.hwnd = NULL;
	sei.nShow = SW_NORMAL;
	if (!ShellExecuteEx(&sei))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_CANCELLED)
		{
			printf("权限获取取消\n");
		}
	}
	else
	{
		printf("重启成功");
		exit(0);
	}
}
