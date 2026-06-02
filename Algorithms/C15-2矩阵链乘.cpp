/*
算法导论15章动态规划的矩阵链乘的实现

最近AI code的发展进度，让我发现现在写代码变成了和之前做web一样了。
现在是AI写完之后，我们自己来读代码和做调整。
这里的代码80%是AI的，我做了剩下的调整工作。
*/

#include <iostream>
#include <string>
#include<vector>
using std::cin;
using std::endl;
using std::cout;
using std::ends;
using std::string;
using std::vector;

//矩阵链乘的动态规划
static void matrixChainOrder(const vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = p.size() - 1;
    // 初始化 m 和 s 的大小为 (n+1)*(n+1)，下标从 1 开始使用
    m.assign(n + 1, vector<int>(n + 1, 0));
    s.assign(n + 1, vector<int>(n + 1, 0));

    // l 为当前计算的链长度
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;     // 初始化为无穷大
            for (int k = i; k <= j - 1; ++k) {
                // 计算代价：左半部分 + 右半部分 + 合并代价
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;   // 记录最优分割点
                }
            }
        }
    }
}
//输出最优括号化方案
static void printOptimalParens(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}
int main() {
    //p为矩阵规模序列，这里测试使用硬编码
    vector<int> p = { 20,26,5,21,17,51 };
    vector<vector<int>> m, s;
    matrixChainOrder(p, m, s);

    cout << "最小标量乘法次数为：" << m[1][p.size() - 1] << endl;
    cout << "最优括号化方案为：";
    printOptimalParens(s, 1, p.size() - 1);
    cout << endl;

    return 0;
}

