#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e4 + 10;
int dp[MAXN];
int a[MAXN];
int n, k;

void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
}

int ans;

void run() {
	for (int i = 1; i <= n; i++) {
		dp[i] = (a[i] + k) * n;
		for (int j = 1; j < i; j++) {
			chkmin(dp[i], dp[j] + (n - j) * (a[i] - a[j] + k));
		}
	}
	ans = dp[n];
}

void write() {
	cout << ans;
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