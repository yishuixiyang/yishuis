/*
算法导论第七章的快速排序

代码中实现了书中的几种快速排序的实现，
并且加入的Dijkstra的三向切分法的快速排序
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int AHeapSize = 0;
void* (*ciallo)(size_t) = malloc;
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
int THREE_MID_RANDOM(int* A, int p, int r)//三数取中，但是会选中重复下标
{
	int r1 = random(p, r);
	int r2 = random(p, r);
	int r3 = random(p, r);
	if ((A[r1] - A[r2]) * (A[r1] - A[r3]) <= 0) return r1;
	if ((A[r2] - A[r1]) * (A[r2] - A[r3]) <= 0) return r2;
	if ((A[r3] - A[r2]) * (A[r3] - A[r1]) <= 0) return r3;
}
//排序函数
void swap(int* a, int* b)//交换元素
{
	int t = *a;
	*a = *b;
	*b = t;
}

int PARTITION(int* A, int p, int r)
{
	int x=A[r];
	int i = p - 1,t=0;
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
int PARTITION_HOARE(int* A, int p, int r)//快速排序发明者 Tony Hoare 最初使用的方法
{
	int x = A[p];
	int left = p+1, right = r;
	while (left < right)
	{
		while(A[left] <= x) left++;
		while(A[right] > x) right--;
		if (left >= right) break;
		swap(&A[left], &A[right]);
	}
	swap(&A[right], &A[p]);
	return right;
}
void PARTITION_Dijkstra(int* A, int p, int r,int *lt,int *gt)//三向切分法
{
	int pivort = A[random(p, r)], i = p;
	*lt = p, *gt = r;
	while(i<=*gt)
	{
		if (A[i] < pivort)
		{
			swap(&A[*lt], &A[i]);
			(*lt)++;
			i++;
		}
		if (A[i] > pivort)
		{
			swap(&A[*gt], &A[i]);
			(*gt)--;
		}
		if (A[i] == pivort)
		{
			i++;
		}
	}
}

void QUICKSORT(int* A, int p, int r)//快速排序
{
	if (p < r)
	{
		int q = 0;
		q = PARTITION(A, p, r);
		QUICKSORT(A, p, q - 1);
		QUICKSORT(A, q + 1, r);
	}
}
void RANDOMIZED_QUICKSORT(int* A, int p, int r)//快速排序-随机化版本
{
	if (p < r)
	{
		int q = 0;
		q = RANDOMIZED_PARTITION(A, p, r);
		RANDOMIZED_QUICKSORT(A, p, q - 1);
		RANDOMIZED_QUICKSORT(A, q + 1, r);
	}
}
void QUICKSORT_HOARE(int* A, int p, int r)//Hoare的快速排序
{
	if (p < r)
	{
		int q = 0;
		q = PARTITION_HOARE(A, p, r);
		QUICKSORT(A, p, q - 1);
		QUICKSORT(A, q + 1, r);
	}
}
void Dijkstra_QUICKSORT(int* A, int p, int r)//Dijkstra的三向切分快速排序
{
	if (p < r)
	{
		int lt=0,gt=0;
		PARTITION_Dijkstra(A, p, r, &lt, &gt);
		Dijkstra_QUICKSORT(A, p, lt - 1);
		Dijkstra_QUICKSORT(A, gt + 1, r);
		
	}
}
void TAIL_RECURSIVE_QUICKSORT(int* A, int p, int r)//尾递归快速排序
{
	int q = 0;
	while (p < r)
	{
		q = PARTITION(A, p, r);
		TAIL_RECURSIVE_QUICKSORT(A, p, q - 1);
		p = q + 1;
	}
}
void RE_TAIL_RECURSIVE_QUICKSORT(int* A, int p, int r)//优化的尾递归快速排序
{
	int q = 0;
	while (p < r)
	{
		q = PARTITION(A, p, r);
		if (q - p < r - q)
		{
			RE_TAIL_RECURSIVE_QUICKSORT(A, p, q - 1);
			p = q + 1;
		}
		else
		{
			RE_TAIL_RECURSIVE_QUICKSORT(A, p + 1, r);
			r = q - 1;
		}
	}
}
//输入输出函数
void input(int* A, int n)
{
	for (int i = 0; i < n; i++)
		A[i] = rand() % 30;
}
void output(int* A, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}
int main()
{
	srand(time(NULL));
	int* array = NULL,n=0;

	printf("输入数组大小: \n");
	scanf_s("%d", &n);
	array = calloc(n, sizeof(int));
	if (array == NULL)
	{
		printf("分配失败\n");
		free(array);
		exit(0);
	}

	input(array, n);
	printf("原数组: \n");
	output(array, n);
	RE_TAIL_RECURSIVE_QUICKSORT(array, 0, n - 1);
	printf("排序后数组: \n");
	output(array, n);

	free(array);
	return 0;
}

