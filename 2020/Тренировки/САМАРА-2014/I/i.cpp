#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll
const int MAXN = 1e5 + 10;
const int INF = 1e15 + 10;
int n, c;
int t[MAXN], a[MAXN][2], dp[MAXN][2];

void chkmin(int & x, const int & y) {
	if (y < x) x = y;
}

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 2; j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;
	dp[0][1] = 0;
}

void calc_dp() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2; j++) {
			if (dp[i - 1][j ^ 1] <= t[i]) chkmin(dp[i][j], a[i - 1][j ^ 1] + t[i - 1]);
			if (t[i - 1] + a[i - 1][j] <= t[i]) chkmin(dp[i][j], dp[i - 1][j]);
		}
	}
}

int suff[MAXN];

void calc_suff() {
	suff[n] = INF;
	for (int i = n - 1; i >= 1; i--) {
		suff[i] = t[i + 1];
		if (t[i] + a[i][0] <= t[i + 1]) {
			suff[i] = suff[i + 1];
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	cin >> n >> c;
	for (int i = 1; i <= n; i++)
		cin >> t[i];
	for (int i = 1; i <= n; i++)
		cin >> a[i][0];
	for (int i = 1; i <= n; i++)
		cin >> a[i][1];
	calc_dp();
	calc_suff();
	int ans = INF;
	for (int i = 0; i < n; i++) {
		if (dp[i][1] == INF) continue;
		if (dp[i][1] > t[i + 1]) continue;
		if (a[i][1] + t[i] + c <= suff[i + 1]) {
			chkmin(ans, a[i][1] + t[i] + c);
		}
	}

	if (dp[n][0] != INF) {
		chkmin(ans, dp[n][0] + c);
	}

	if (dp[n][1] != INF) {
		chkmin(ans, a[n][1] + t[n] + c);
	}

	if (ans == INF) {
		cout << "Dire victory" << endl;
	} else {
		cout << "Radiant victory" << endl;
		cout << ans << endl;
	}
	return 0;
}