#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e4 + 10;
int n, m, k;
int a[MAXN];

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

ll dp[MAXN];

void run() {
	for (int i = 0; i < n; i++) {
		int min_val = a[i], max_val = a[i];
		dp[i] = k;
		if (i > 0) dp[i] += dp[i - 1];
		for (int j = i - 1; j >= 0 && i - j + 1 <= m; j--) {
			chkmin(min_val, a[j]);
			chkmax(max_val, a[j]);
			ll fans = k + (ll)(i - j + 1) * (max_val - min_val);
			if (j > 0) fans += dp[j - 1];
			chkmin(dp[i], fans);
		}
	}
}

void write() {
	cout << dp[n - 1] << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}