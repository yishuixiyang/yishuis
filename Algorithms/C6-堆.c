/*维护堆的性质
  

其中数组下标从0开始，PARENT LEFT RIGHT更改了映射方式
函数变量n位堆的大小，函数名遵循算法导论
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int AHeapSize = 0;
void* (*ciallo)(size_t) = malloc;
void output(int A[],int n)
{
	printf("堆：\n");
	for (int i = 0,j=1; i < n; i++)
	{
		if (i == (1 << j)-1)
		{
			printf("\n");
			j++;
		}
		printf("%3d ",A[i]);
	}
	printf("\n\n");
}
int PARENT(int i)
{
	return ((i+1)>>1)-1;
}
int LEFT(int i)
{
	return (i << 1)+1;
}
int RIGHT(int i)
{
	return (i + 1) << 1;
}
void MAX_HEAPIFY(int A[],int i,int n)
{
	int legest = 0;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l<n && A[l]>A[i]) legest = l;
	else legest = i;
	if (r<n && A[r]>A[legest]) legest = r;
	if (legest != i)
	{
		int t = 0;
		t = A[i];
		A[i] = A[legest];
		A[legest] = t;
		MAX_HEAPIFY(A,legest,n);
	}
}
void MIN_HEAPIFY( int A[],int i,int n)
{
	int least = 0;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l<n && A[l]<A[i]) least = l;
	else least = i;
	if (r<n && A[r]<A[least]) least = r;
	if (least != i)
	{
		int t = 0;
		t = A[i];
		A[i] = A[least];
		A[least] = t;
		MAX_HEAPIFY(A,least,n);
	}
}
void BUILD_MAX_HEAP(int A[],int n)//构造最大堆
{
	for (int i = (n >> 1) - 1; i >= 0; i--)
	{
		MAX_HEAPIFY(A,i,n);
	}
}
void BUILD_MIN_HEAP(int A[],int n)//构造最小堆
{
	for (int i = (n >> 1)-1; i >= 0; i--)
	{
		MIN_HEAPIFY(A, i,n);
	}
}
void HEAPSORT(int A[], int n)
{
	int size = n - 1, t = 0;
	BUILD_MAX_HEAP(A, n);
	for (int i = size; i > 0;i--)
	{
		t = A[0];
		A[0] = A[i];
		A[i] = t;
		MAX_HEAPIFY(A,0,size);
		size--;
	}
}
int main()
{
	srand(time(NULL));
	int* heap = NULL;
	int heapb[] = {23,22,17};
	printf("输入堆大小:\n");
	scanf_s("%d", &AHeapSize);
	heap = (int*)ciallo(AHeapSize * sizeof(int));
	if (heap==NULL)
	{
		printf("分配失败");
		exit(0);
	}
	for(int i = 0; i < AHeapSize; i++)
	{
		heap[i] = rand() % 100;
	}
	output(heap,AHeapSize);
	HEAPSORT(heap, AHeapSize);
	//printf("dd");
	output(heap,AHeapSize);

	/*output(heapb,3);
	HEAPSORT(heapb, 3);
	output(heapb,3);*/
}