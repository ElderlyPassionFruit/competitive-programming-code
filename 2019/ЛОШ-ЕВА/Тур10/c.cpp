#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110;
const int INF = 1e18;
int dp[MAXN][MAXN][MAXN];
int ans[MAXN][MAXN];
int n, m;
int a[MAXN][2];
void read() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		cin >> a[i][0] >> a[i][1];
	for (int i = 1; i <= m; i++)
		a[i][1] = a[i][1] + a[i - 1][1];
}

void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			for (int k = 0; k < MAXN; k++)
				dp[i][j][k] = INF;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			ans[i][j] = INF;
	dp[0][0][0] = 0;
	ans[0][0] = 0;
}

void solve() {
	for (int i = 1; i <= m; i++) {
		for (int j = min(i, n); j >= 1; j--) {
			int sum = 0;
			for (int k = 1; k <= i - j + 1; k++) {
				sum += (a[i][1] - a[i - k + 1][1]) * a[i - k + 1][0];
				chkmin(dp[i][j][k], ans[i - k][j - 1] + sum);
				chkmin(ans[i][j], dp[i][j][k]);
			}
		}
	}
}

void run() {
	build();
	solve();
}

void write() {
	cout << ans[m][n] << endl;
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