#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

void output(int a[], int n);
void mer(int a[], int p, int q, int r);
void mer_sort(int a[], int p, int q);
void insert(int array[], int n);

int* L = NULL, * R = NULL;


int main()
{
	int n = 0, end = 0, start = 0;
	int* array = NULL;
	srand(time(NULL));

	printf("输入数量: ");
	scanf_s("%d", &n);
	array = (int*)malloc(n * sizeof(int));
	L = (int*)malloc(n * sizeof(int));
	R = (int*)malloc(n * sizeof(int));
	if (L == NULL || R == NULL || array == NULL)
	{
		free(L), free(R), free(array);
		printf("指针分配失败\n");
		exit(0);
	}


	for (int i = 0; i < n; i++)
	{
		array[i] = rand() % 999 + 1;
	}

	//output(array, n);
	start = clock();
	mer_sort(array, 0, n - 1);
	end = clock();
	printf("归并 %.9lf ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
	//output(array, n);

	for (int i = 0; i < n; i++)
	{
		array[i] = rand() % 999 + 1;
	}
	start = clock();
	insert(array, n);
	end = clock();
	printf("插入 %.9lf ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
	free(L), free(R), free(array);
	return 0;
}



void output(int a[], int n)
{
	printf("数组：\n");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", a[i]);
	}
	printf("\n");
}
void mer(int a[], int p, int q, int r)
{

	for (int i = 0; i < q - p + 1; i++)
		L[i] = a[i + p];
	for (int i = 0; i < r - q; i++)
		R[i] = a[i + q + 1];

	for (int k = p, i = 0, j = 0; k <= r; k++)
	{
		if (i == q - p + 1)
		{
			a[k] = R[j];
			j++;
			continue;
		}
		if (j == r - q)
		{
			a[k] = L[i];
			i++;
			continue;
		}
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
	}
}
void mer_sort(int a[], int p, int q)
{
	if (q > p)
	{
		mer_sort(a, p, (p + q) / 2);
		mer_sort(a, (p + q) / 2 + 1, q);
		mer(a, p, (p + q) / 2, q);
	}
}
void insert(int array[], int n)
{
	int a = 0, j = 0;
	for (int i = 1; i < n; i++)
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