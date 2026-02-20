#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int AHeapSize = 0;
void* (*ciallo)(size_t) = malloc;

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
void QUICKSORT(int* A, int p, int r)//快速排序
{
	if (p < r)
	{
		int q = 0;
		q = PARTITION_HOARE(A, p, r);
		QUICKSORT(A, p, q - 1);
		QUICKSORT(A, q + 1, r);
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
	QUICKSORT(array, 0, n - 1);
	printf("排序后数组: \n");
	output(array, n);

	free(array);
	return 0;
}