/*
	算法导论第八章 线性时间排序
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int AHeapSize = 0;
void* (*ciallo)(size_t) = malloc;//Ciallo～(∠・ω< )⌒★
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
		if (i % 10 == 9) printf("\n");
	}
	printf("\n");
}

//计数函数  A B不能相同 临时数组范围[0..k]
static void COUNTING_SORT(int* A, int* B,int n, int k)
{
	//临时数组C需要全0
	int* C = (int*)calloc(k + 1, sizeof(int));
	if (C == NULL)
	{
		printf("临时数组分配失败\n");
		free(C);
		return;
	}
	//统计个数
	for (int i = 0; i < n; i++)
		C[A[i]]++;
	//把C转换成前缀和数组，C[i]表示小于等于i的元素的个数
	for (int i = 1; i <= k; i++)
		C[i] = C[i] + C[i - 1];
	//把C放入B中 小于等于A[i]的元素个数有m，则A[i]放入B[m-1]
	for (int i = n - 1; i >= 0; i--)
	{
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;//结束后C为全零
	}
	free(C);
}
int main()
{
	int* array = NULL, n = 0;
	int* outarray = NULL, k = 0;

	printf("输入数组大小: \n");
	scanf_s("%d", &n);
	array = calloc(n, sizeof(int));
	outarray = calloc(n, sizeof(int));
	if (array == NULL||outarray==NULL)
	{
		printf("分配失败\n");
		free(array);
		free(outarray);
		exit(0);
	}

	input(array, n);

	printf("原数组: \n");
	output(array, n);

	COUNTING_SORT(array, outarray, n, 99);

	printf("排序后数组: \n");
	output(outarray, n);

	free(array);
	free(outarray);

	return 0;
}