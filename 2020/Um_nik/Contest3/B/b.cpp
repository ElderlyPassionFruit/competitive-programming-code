#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 317;

int n, m, x;
int dp[2][MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> x;
	if (n > m) {
		cout << 0 << endl;
		return 0;
	}
	assert(n < MAXN);
	dp[0][0][0] = 1;
	for (int i = 0; i < m; i++) {
		for (int bal = 0; bal <= n; bal++) {
			for (int cntL = 0; cntL <= n; cntL++) {
				if (i + 1 == x) {
					if (max(cntL, bal) == n) continue;
					dp[1][bal + 1][cntL + 1] = add(dp[1][bal + 1][cntL + 1], dp[0][bal][cntL]);
					dp[1][bal][cntL + 1] = add(dp[1][bal][cntL + 1], dp[0][bal][cntL]);
				} else {
					if (max(cntL, bal) < n) {
						dp[1][bal + 1][cntL + 1] = add(dp[1][bal + 1][cntL + 1], dp[0][bal][cntL]);
						dp[1][bal][cntL + 1] = add(dp[1][bal][cntL + 1], dp[0][bal][cntL]);
					}
					if (bal > 0) {
						dp[1][bal - 1][cntL] = add(dp[1][bal - 1][cntL], dp[0][bal][cntL]);
					}
				}
			}
		}
		for (int bal = 0; bal <= n; bal++) {
			for (int cntL = 0; cntL <= n; cntL++) {
				if (i + 1 == x) dp[0][bal][cntL] = 0;
				dp[0][bal][cntL] = add(dp[0][bal][cntL], dp[1][bal][cntL]);
				dp[1][bal][cntL] = 0;
			}
		}
	}
	int ans = dp[0][0][n];
	for (int i = 1; i <= n; i++) {
		ans = mul(ans, i);
	}
	cout << ans << endl;
	return 0;
}
