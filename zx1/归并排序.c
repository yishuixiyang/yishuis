#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

void output(int a[], int n);
void mer(int a[], int p, int q, int r);
void mer_sort(int a[], int p, int q);

int main()
{
	int n = 0;
	int array[30] = { 0 };
	srand(time(NULL));

	printf("输入数量: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		array[i] = rand() % 20 + 1;
	}

	output(array, n);
	mer_sort(array, 0, n - 1);
	output(array, n);

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
	int L[30] = { 0 }, R[30] = { 0 };

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