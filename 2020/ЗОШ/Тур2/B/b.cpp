#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
//#define int ll
const int MAXX = 110, MAXN = 1e5 + 10;
int n;
int dp[MAXN][MAXX];
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
}

int ans;

void run() {
	ans = 1e9;
	for (int i = 0; i < MAXX; i++)
		dp[1][i] = 1e9;
	dp[1][0] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < MAXX; j++) {
			dp[i][j] = 1e9;
			if (a[i] >= j) {
				for (int k = max(0LL, j - 1); k <= min(MAXX - 1, j + 1); k++) {
					chkmin(dp[i][j], abs(j - a[i]) + dp[i - 1][k]);
				}
			}
		}
	}

	/*cout << "n = " << n << endl;
	cout << "A = " << endl;
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;

	cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 10; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}*/

	for (int i = 0; i <= 1; i++)
		chkmin(ans, dp[n][i]);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}