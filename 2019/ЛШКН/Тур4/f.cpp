#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e4 + 10;
int dp[MAXN];
int pred[MAXN];
int p[MAXN], s[MAXN];
int n, c;

void read() {
	cin >> n >> c;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
}

int ans = 1e18;

void run() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = 1e18;
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++)
			pred[j] = 1e18;

		for (int j = 0; j <= i; j++) {
			chkmin(pred[j + 1], dp[j] + s[i]);
			chkmin(pred[j], dp[j] + p[i] + c * j);
		}
		for (int j = 0; j <= n; j++)
			dp[j] = pred[j];
	}

	for (int i = 0; i <= n; i++) {
		chkmin(ans, dp[i]);
	}
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