#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


const int MOD = 1000000009;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

const int MAXN = 110;
int dp[MAXN][MAXN][MAXN];

int n, m, len;

void read() {
	cin >> n >> m >> len;
	if (len == 1) {
		cout << 1 << endl;
		exit(0);
	}
}

void run() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < MAXN; k++) {
				dp[i][j][k] = 0;
			}
		}
	}
	dp[0][0][0] = 1;

	for (int i = 0; i < m; i++) {
		for (int pos_next = 1; pos_next + len - 1 <= n; pos_next++) {
			dp[i + 1][pos_next][1] = add(dp[i + 1][pos_next][1], dp[i][0][0]);
		}
		if (i + len <= m) {
			dp[i + len][0][0] = add(dp[i + len][0][0], dp[i][0][0]);
		}
		
		if (n == len) {
			dp[i + 1][0][0] = add(dp[i + 1][0][0], dp[i][0][0]);
		}

		if (n > len)
		for (int j = 1; j + len - 1 <= n; j++) {
			for (int k = 1; k <= min(i, len - 1); k++) {
				if (dp[i][j][k] == 0) continue;
				int x = dp[i][j][k];	

				if (k + 1 < len)
					dp[i + 1][j][k + 1] = add(dp[i + 1][j][k + 1], x);
				else {
					dp[i + 1][0][0] = add(dp[i + 1][0][0], x);
				}
				if (i + len <= m)
					dp[i + len][j][k] = add(dp[i + len][j][k], x);
			}
		}
	}
}

void write() {
	cout << dp[m][0][0] << endl;
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