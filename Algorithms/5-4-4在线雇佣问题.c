#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void* (*ciallo)(size_t) = malloc;
int score()
{
	return rand() % 100 + 1;
}
int on_line_maximum(int n)
{
	int k = n / exp(1);
	int bestscore = -1, t = 0;
	for (int i = 0; i < k; i++)
	{
		t = score();
		if (t > bestscore)
			bestscore = t;
	}
	for (int i = k + 1; i < n; i++)
	{
		t = score();
		if (t > bestscore) return t;
	}
	return score();
}

int main()
{
	srand(time(NULL));
	int n = 0;
	printf("面试人数:\n");
	scanf_s("%d", &n);
	printf("雇用分数:%d ", on_line_maximum(n));
	return 0;
}