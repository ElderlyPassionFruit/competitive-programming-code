#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}

int n, k;

void read() {
	cin >> n >> k;
}

const int MAXN = 110, MAXK = 1510;

int dp[MAXN][MAXK];
int ans;
void run() {
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			for (int last = 0; last < 16 && j - last >= 0; last++) {
				dp[i][j] = add(dp[i][j], dp[i - 1][j - last]);
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/
	ans = sub(dp[n][k], dp[n - 1][k]);
}

void write() {
	cout << ans << endl;
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