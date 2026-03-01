/*
	算法导论第八章 线性时间排序

	文件是utf-8编码65001
	写了基数排序按二进制位排序的形式
	引理8-4的每次按r位二进制排序没有实现（因为左移会溢出）
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
		//if (i % 10 == 9) printf("\n");
	}
	printf("\n");
}

//计数排序  A B不能相同 临时数组范围[0..k]
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
	for (int i = n - 1; i >= 0; i--)//从n-1遍历到0，保证稳定排序
	{
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
	free(C);
}
//基数排序 内部排序使用计数排序
static void RADIX_SORT(int* A,int n, int d)
{
	int* B = (int*)calloc(n, sizeof(int));
	if (B == NULL) { printf("分配失败\n"); return; }
	int muti = 1;//A[i]/miti%10用来取A[i]的一位数字
	for (int i = 1; i <= d; i++)
	{
		int C[10] = { 0 };
		for (int j = 0; j < n; j++)
		{
			C[A[j]/muti % 10]++;

		}
		for (int j = 1; j < 10; j++)
			C[j] = C[j] + C[j - 1];
		for (int j = n - 1; j >= 0; j--)
		{
			B[C[A[j]/muti%10] - 1] = A[j];
			C[A[j]/muti%10]--;
		}
		for (int j = 0; j < n; j++) //排序后修改原数组
			A[j] = B[j];
		muti *= 10;
	}
	free(B);

}
//基数排序 二进制版本
static void BINARY_RADIX_SORT(int* A,int n, int d)
{
	int* B = (int*)calloc(n, sizeof(int));
	if (B == NULL) { printf("分配失败\n"); return; }
	int C[2] = { 0 };
	//A[j] >> (n - 1) & 1用来取A[j]的第n位数字
	for (int i = 1; i <= d; i++)
	{
		C[0] = 0, C[1] = 0;
		for (int j = 0; j < n; j++)
		{
			C[A[j] >> (i - 1) & 1]++;

		}
		C[1] += C[0];
		for (int j = n - 1; j >= 0; j--)
		{
			B[C[A[j] >> (i - 1) & 1] - 1] = A[j];
			C[A[j] >> (i - 1) & 1]--;
		}
		for (int j = 0; j < n; j++) //排序后修改原数组
			A[j] = B[j];
	}
	free(B);

}
int main()
{
	srand(time(NULL));
	//计数排序测试
	/*int* array = NULL, n = 0;
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

	printf("计数排序后数组: \n");
	output(outarray, n);

	free(array);
	free(outarray);*/

	//基数排序测试
	int* array = NULL, n = 0;

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

	BINARY_RADIX_SORT(array,n, 7);

	printf("基数排序后数组: \n");
	output(array, n);

	free(array);

	return 0;
}