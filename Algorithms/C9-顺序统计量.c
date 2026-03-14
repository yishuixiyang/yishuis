/*
*  中位数和顺序统计量
*	引入了C7中的部分函数
*   因为个人时间问题，部分代码会使用AI来编写，但是思路还是自己想的。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

static void* (*ciallo)(size_t) = malloc;
//输入函数
static void input(int* A, int n)
{
	for (int i = 0; i < n; i++)
		A[i] = random(0,99);
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
//排序函数
static int PARTITION(int* A, int p, int r)
{
	int x = A[r];
	int i = p - 1;
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
static int RE_PARTITION(int* A, int p, int r,int x)
{
	int i = p - 1;
	for (int j = p; j <= r; j++)
	{
		if (A[j] == x)
		{
			swap(&A[j], &A[r]);
			break;
		}
	}
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(&A[j], &A[i]);
		}
	}
	swap(&A[i+1], &A[r]);
	return i + 1;
}
static int RANDOMIZED_PARTITION(int* A, int p, int r)
{
	int i = random(p, r);
	swap(&A[i], &A[r]);
	return PARTITION(A, p, r);
}
static void insert(int array[], int p,int r)
{
	int a = 0, j = 0;
	for (int i = p+1; i <= r; i++)
	{
		a = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > a)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = a;
	}
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
//循环版本的期望为线性时间的选择算法
static int RANDOMIZED_SELECT_ITERATIVE(int* A, int p, int r, int i)
{
	int k = 0, q = 0;
	while (p < r)
	{
		q = RANDOMIZED_PARTITION(A, p, r);
		k = q - p + 1;
		if (i == k) return A[q];
		else if (i < k) r = q - 1;
		else
		{
			p = q + 1;
			i = i - k;
		}
	}
	return A[p];
}
//最坏情况为线性时间的选择算法
static int SELECT(int* A, int p, int r, int i)  //O(n)=cn c>=20
{
	if (p == r) return A[p];
	int sum = ceil((r - p + 1) / 5.0);
	int *mid = (int*)calloc(sum, sizeof(int));
	if (mid == NULL) { printf("分配失败\n"); exit(EXIT_FAILURE); }
	int t = 0, s = 0;
	for (int k = 0; k <sum; k++)
	{
		t = p + 5 * k;
		s = t + 4 > r ? r : t + 4;
		insert(A, t, s);
		mid[k] = A[t+(s-t)/2];
	}
	int x = SELECT(mid, 0, sum - 1, (sum + 1) >> 1);
	free(mid);
	int q = RE_PARTITION(A, p, r, x);
	int k = q - p + 1;

	if (i == k) return A[q];
	else if (i < k)	return SELECT(A, p, q - 1, i);
	else return SELECT(A, q + 1, r, i - k);
}
int main()
{
	//srand(time(NULL));
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
	s = SELECT(array, 0, n - 1, (n + 1) >> 1);
	printf("最大值: %d 最小值: %d\n 中位数 %d \n", max, min, s);
	output(array, n);
	free(array);
}