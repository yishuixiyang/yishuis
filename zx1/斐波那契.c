#include <stdio.h>
#include <string.h>
long long fb(int n){
	if (n == 1)	return 1;
	if (n == 2) return 1;
	return fb(n - 1) + fb(n - 2);
}
int main(){
	long long n,sum=0;
	char h[30],e[30];
	while (1) {
		printf("请输入整数n，进行求和:\n");
		scanf_s("%lld", &n);
		if (n > 0 && n < 91) {
			break;
		}
		else if (n <= 0 || n >= 91) {
			continue;
		}
		else {
			printf("输入错误，使用默认n=1");
			n = 1;
			break;
		}
	}
	printf("数列：");
	for (int i = 1;i < n;i++) {
		sum += fb(i);
		printf("%lld,", fb(i));
	}
	printf("%lld\n", fb(n));
	long double v = (long double)fb(n-1) / fb(n);
	sprintf_s(h,sizeof(h), "%lld", sum);
	sprintf_s(e, sizeof(e),"%lf", v);
	printf("斐波那契数列前%lld项和:%s\n黄金分割率:%s\n", n, h,e);
	return 0;
 }