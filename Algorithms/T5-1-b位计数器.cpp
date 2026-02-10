/*
 算法导论 思考题5-1
 其中n(i)使用函数实现
*/
#include <random>
#include <iostream>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0.0, 1.0);
int ni(int i)  //这里输出可以自己定义
{
	return 10*i;
}
int INCREMENT(int a,int b ) //a=n(i+1) b=n(i)
{
	double random = dis(gen);
	double p = 1.0 / (a - b);
	//std::cout << random<<" " << p << std::endl;
	if (p >= random) return 1;
	else return 0;
}
int main()
{
	int n = 0,b=0,result=0;
	//n是计数器执行次数，b是计数器位数，result是计数器显示的结果
	std::cout << "输入随机次数和计数器位数：" << std::endl;
	std::cin >> n>>b;
	for (int i = 1; i <= n; i++)
	{
		if (result == (1 << b) - 1) break;
		result += INCREMENT(ni(result + 1), ni(result));
		std::cout <<"["<<i<< "]计数器显示" << result << ",对应n(" << result << ")：" << ni(result) << std::endl;
		//printf( "[%d]计数器显示%d,对应n(%d)：%d\n",i, result, result, ni(result) );
	}
}