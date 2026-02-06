#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define bit10 65 //范围从 0到(10^bit10)-1   n*10^(bit10-1) 0<n<10 都可以表示
void* (*ciallo)(size_t) = malloc;
typedef int BN[bit10];
void add(BN a, BN b,int offset) //a*10^offset+b -> a
{
	for (int i = 0; i < bit10-offset; i++)
	{
		a[i+offset] += b[i];
		if (a[i+offset] > 9 && i+offset+1<bit10)
		{
			a[i + 1+offset]++;
			a[i+offset] -= 10;
		}
	}
}
void multi(BN c,BN a, int b) //因数乘法c默认是全0 a*b -> c
{
	if (b == 0)
	{
		for (int i = 0; i < bit10; i++) c[i] = 0;
		return;
	}
	for (int i = 0; i < bit10; i++)
	{
		c[i]+=b*a[i];
		if (c[i] > 9 && i+1< bit10)
		{
			c[i + 1]=c[i]/10;
			c[i] %= 10;
		}
	}
}
void MUL(BN a, BN b) // a*b -> a
{
	BN c = { 0 };
	for (int i = 0; i < bit10; i++)
	{
		BN temp = { 0 };
		multi(temp,a, b[i]);
		add(c, temp, i);
	}
	for (int i = 0; i < bit10; i++) a[i] = c[i];
}
void output(BN a) //输出a，末尾不换行
{
	int read = bit10-1;
	while (!a[read])read--;
	for (int i = read; i >= 0; i--)
	{
		printf("%d", a[i]);
	}
}
void int_to_BN(BN a, int b)//int转换成BN
{
	for (int i = 0; i < bit10; i++)
	{
		a[i] = b % 10;
		b /= 10;
		if (b == 0) return;
	}
}
int main()
{
	int n = 0;
	BN sum = { 0};
	BN ad = { 1}, b = { 0 }, c = { 1 };
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		add(b, c, 0);  //b++
		MUL(ad, b);    //计算n!
		add(sum, ad, 0);  //sum+=n!
	}
	output(sum);
	return 0;
}