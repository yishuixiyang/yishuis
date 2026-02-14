/*维护堆的性质
* 
其中数组下标从0开始，PARENT LEFT RIGHT更改了映射方式
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int AHeapSize = 0;
void* (*ciallo)(size_t) = malloc;
void output(int A[])
{
	for (int i = 0; i < AHeapSize; i++)
	{
		printf("%d:%d ", i + 1, A[i]);
	}
	printf("\n");
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
void MAX_HEAPIFY(int i,int A[])
{
	int legest = 0;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l<AHeapSize && A[l]>A[i]) legest = l;
	else legest = i;
	if (r<AHeapSize && A[r]>A[legest]) legest = r;
	if (legest != i)
	{
		int t = 0;
		t = A[i];
		A[i] = A[legest];
		A[legest] = t;
		MAX_HEAPIFY(legest, A);
	}
}
void MIN_HEAPIFY(int i, int A[])
{
	int least = 0;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l<AHeapSize && A[l]<A[i]) least = l;
	else least = i;
	if (r<AHeapSize && A[r]<A[least]) least = r;
	if (least != i)
	{
		int t = 0;
		t = A[i];
		A[i] = A[least];
		A[least] = t;
		MAX_HEAPIFY(least, A);
	}
}
int main()
{
	srand(time(NULL));
	int* heap = NULL;
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
		heap[i] = rand() % 30;
	}
	output(heap);
	MAX_HEAPIFY(0, heap);
	output(heap);
	MIN_HEAPIFY(0, heap);
	output(heap);
}