#include <stdio.h>

int main()
{
	long long a=0,t=0;
	long long sp[100] = {0};
	long long num[100] = { 0 };
	num[a] = 1;

	printf("物种等级和时间：");
	scanf_s("%lld%lld", &a,&t);

	for (long long i = 0;i < 100;i++)
	{
		sp[i] = i;
	}
	for (long long i = 0;i < t;i++)
	{
		for (long long j = a;j >0;j--)
		{
			if (num[j] != 0) num[j - 1] = num[j - 1] + sp[j] * num[j];
			else continue;
		}
	}

	printf("%lld", num[0]);
	return 0;
}
