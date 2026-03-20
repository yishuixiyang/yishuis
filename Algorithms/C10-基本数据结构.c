/*
*   基本数据结构
*	引入了C7中的部分函数
*   
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
//栈定义
typedef struct {
	int top;
	int maxsize;
	int *stack;
} STACK;

static void* (*ciallo)(size_t) = malloc;
//输入函数
static void input(int* A, int n)
{
	for (int i = 0; i < n; i++)
		A[i] = random(0, 99);
}
//输出函数 
static void output(int* A, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%2d ", A[i]);
		//if (i % 10 == 9) printf("\n");
	}
	printf("\n");
}
//辅助函数
static void swap(int* a, int* b)//交换元素
{
	int t = *a;
	*a = *b;
	*b = t;
}
//随机函数
static int basic_random()
{
	int a = 0, b = 0;
	while (1)
	{
		a = rand() % 2;
		b = rand() % 2;
		if (a != b) return a;
	}
}
static int random(int a, int b) //随机生成[a..b]的整数范围Z
{
	int n = b - a, size = 0, num = 0;
	if (n == 0) return a;
	while ((2 << size) < n + 1) size++;
	while (1) {
		num = 0;
		for (int i = 0; i <= size; i++) {
			num <<= 1;
			num ^= basic_random();
			//num ^= rand()%2;
		}
		if (num >= 0 && num <= n) return num + a;
	}
}

//栈判空 栈为空返回1
static int EMPTY(STACK * S)
{
	if (S->top == -1) return 1;
	else return 0;
}
//栈压入
static void PUSH(STACK* S, int x)
{
	if (S->maxsize == S->top + 1)
	{
		printf("%d 压入错误：栈已满\n",x);
		return;
	}
	S->top++;
	S->stack[S->top] = x;
}
//栈弹出
static int POP(STACK* S)
{
	if (EMPTY(S))
	{
		printf("错误：栈已空\n");
		return -1;
	}
	S->top--;
	return S->stack[S->top+1];
}

int main()
{
	//栈测试
	STACK sta = {-1,0,NULL};
	STACK* p = &sta;
	printf("输入栈容量:");
	scanf_s("%d", &sta.maxsize);
	sta.stack = (int*)calloc(sta.maxsize, sizeof(int));
	if (sta.stack == NULL) { printf("分配失败\n"); return 1; }
	PUSH(p, 1);
	PUSH(p, 2);
	PUSH(p, 2);
	PUSH(p, 2);
	output(p->stack, p->top + 1);

}