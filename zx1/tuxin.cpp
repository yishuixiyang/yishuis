#include<iostream>
#include <string.h>
using namespace std;
const int N = 1 << 20 | 5;
char s[N];
int n, z[N], pre[N], suf[N], cnt[27], dif[N];
void solve() {
	cin>>s[1]; n = strlen(s+1);
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++) {
		if (i <= r)z[i] = min(z[i - l + 1], r - i + 1);
		while (s[1 + z[i]] == s[i + z[i]])z[i]++;
		if (i + z[i] - 1 > r)l = i, r = i + z[i] - 1;
	}
	memset(cnt, 0, sizeof cnt);
	int odd = 0;
	for (int i = 1; i <= n; i++) {
		int x = s[i] - 'a';
		cnt[x] ^= 1;
		odd += cnt[x] ? 1 : -1;
		pre[i] = odd;
	}
	memset(cnt, 0, sizeof cnt);
	odd = 0;
	for (int i = n; i >= 1; i--) {
		int x = s[i] - 'a';
		cnt[x] ^= 1;
		odd += cnt[x] ? 1 : -1;
		suf[i] = odd;
	}
	memset(dif, 0, sizeof dif);
	for (int i = 2; i <= n; i++) {
		int max_k = (n - i + 1) / (i - 1);
		if (max_k >= 1) {
			dif[1]++;
			if (max_k >= 2) {
				int len = i - 1;
				if (z[len + 1] >= len) dif[2]++, dif[max_k + 1]--;
				else dif[2]++, dif[2 + (z[len + 1] < len ? 1 : 0)]--;
			}
		}
	}
	for (int i = 1; i <= n; i++)dif[i] += dif[i - 1];
	long long ans = 0;
	for (int i = 2; i < n; i++)if (pre[i] <= suf[i + 1])ans += dif[(n - i) / (i - 1) + 1];
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T; while (T--)solve();
	return 0;
}