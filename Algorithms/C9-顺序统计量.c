/*
*  中位数和顺序统计量
*	引入了C7中的部分函数
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* (*ciallo)(size_t) = malloc;
//输入函数
static void input(int* A, int n)
{
	for (int i = 0; i < n; i++)
		A[i] = rand() % 100;
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
void swap(int* a, int* b)//交换元素
{
	int t = *a;
	*a = *b;
	*b = t;
}
//随机函数
int basic_random()
{
	int a = 0, b = 0;
	while (1)
	{
		a = rand() % 2;
		b = rand() % 2;
		if (a != b) return a;
	}
}
int random(int a, int b) //随机生成[a..b]的整数范围Z
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
//排序函数
int PARTITION(int* A, int p, int r)
{
	int x = A[r];
	int i = p - 1, t = 0;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(&A[j], &A[i]);
		}
	}
	swap(&A[i + 1], &A[r]);
	return i + 1;
}
int RANDOMIZED_PARTITION(int* A, int p, int r)
{
	int i = random(p, r);
	swap(&A[i], &A[r]);
	return PARTITION(A, p, r);
}


//选择最大和最小值
static void MIN_MAX_SELECT(int* A, int n, int* max, int* min)
{
	if (n == 0) return;
	if (n % 2 == 1)
	{
		*max = *min = A[0];
		for (int i = 2; i < n; i+=2)
		{
			if (A[i] > A[i - 1])
			{
				*max = A[i] > *max ? A[i] : *max;
				*min = A[i-1] < *min ? A[i-1] : *min;
			}
			else
			{
				*max = A[i-1] > *max ? A[i-1] : *max;
				*min = A[i] < *min ? A[i] : *min;
			}
		}
	}
	else
	{
		*max = A[0] > A[1] ? A[0] : A[1];
		*min = A[0] < A[1] ? A[0] : A[1];
		for (int i = 3; i < n; i += 2)
		{
			if (A[i] > A[i - 1])
			{
				*max = A[i] > *max ? A[i] : *max;
				*min = A[i - 1] < *min ? A[i - 1] : *min;
			}
			else
			{
				*max = A[i - 1] > *max ? A[i - 1] : *max;
				*min = A[i] < *min ? A[i] : *min;
			}
		}
	}
}
//期望为线性时间的选择算法
static int RANDOMIZED_SELECT(int *A,int p,int r,int i)
{
	if (p == r) return A[p];
	int q = RANDOMIZED_PARTITION(A, p, r);
	int k = q - p + 1;
	if (i == k) return A[q];
	else if (i < k)	return RANDOMIZED_SELECT(A, p, q - 1, i);
	else return RANDOMIZED_SELECT(A, q + 1, r, i - k);
}
int main()
{
	int* array = NULL, n = 0;
	int max = 0, min = 0,s=0;
	printf("输入数组大小: \n");
	scanf_s("%d", &n);
	array = calloc(n, sizeof(int));
	if (array == NULL){printf("分配失败\n");free(array);exit(0);}

	input(array, n);

	printf("原数组: \n");
	output(array, n);

	MIN_MAX_SELECT(array, n, &max, &min);
	s=RANDOMIZED_SELECT(array, 0, n - 1, 4);
	printf("最大值: %d 最小值: %d\n第4个顺序统计量 %d \n", max, min,s);
	output(array, n);
	free(array);
}