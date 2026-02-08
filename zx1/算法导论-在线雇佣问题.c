/*
算法导论（第三版） 
5.4.4 在线雇佣问题的最终代码实现
其中使用了结论中的k=n/e

Introduction to Algorithms (Third Edition)
5.4.4 Final code implementation for the online hiring problem
which uses the conclusion k = n/e
*/

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
	int bestscore = -1,t=0;
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