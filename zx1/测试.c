#include<stdio.h>

int main()
{
	unsigned int a = 0, b = 0, p = 0,scale=1,s=1;
	scanf_s("%u%u%u", &a, &b, &p);
	scale = a;
	for (int i = 0; i < 32; i++)
	{
		if (b & ((unsigned int)1 << i))
		{
			s = (s*scale)%p;
		}
		scale = ((scale % p) * (scale % p))%p;
	}
	printf("%u", s);
	return 0;
	
}
