#include <bits/stdc++.h>

using namespace std;
#define int unsigned long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110, MAXD = 20;
int n;
void read() {
	cin >> n;
}

int dp[MAXN][MAXD];

void run() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXD; j++)
			dp[i][j] = 0;
	dp[0][0] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 2; j < MAXD - 1; j++)
			dp[i][0] += dp[i - 1][j];
		for (int j = 1; j < MAXD; j++)
			dp[i][j] = dp[i - 1][j - 1];
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < MAXD; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}*/
}

void write() {
	int ans = 0;
	for (int i = 1; i < MAXD; i++)
		ans += dp[n - 1][i];
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