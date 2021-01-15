#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 41;
const int INF = 1e9 + 228;
const int MAXVAL = 101;
const int MAXSUM = MAXVAL * MAXN;

int n;
short int a[MAXN];
bitset<MAXSUM> dp[2][MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int calc(int mx1, int mx2) {
	for (int i = 0; i < n; i++)
		dp[0][i] &= 0, dp[1][i] &= 0;
	dp[0][1][a[mx1]] = 1;

	for (int i = 0; i < n; i++) {
		if (mx1 == i) continue;
		if (mx2 == i) continue;
		if (max(a[mx1], a[mx2]) < a[i]) {
			return INF;
		}
		if (a[mx1] >= a[i]) {
			for (int cnt = 0; cnt < n - 1; cnt++) {
				dp[1][cnt + 1] |= dp[0][cnt] << a[i];
			}
		}
		if (a[mx2] >= a[i]) {
			for (int cnt = 0; cnt < n; cnt++) {
				dp[1][cnt] |= dp[0][cnt];
			}
		}
		for (int cnt = 0; cnt < n; cnt++) {
			dp[0][cnt] = dp[1][cnt];
			dp[1][cnt] &= 0;
		}
	}
	int all = 0;
	for (int i = 0; i < n; i++) {
		all += a[i];
	}
	int ans = INF;
	for (int cnt = 2; n - cnt >= 2; cnt++) {
		for (int sum = 0; sum <= all; sum++) {
			if (!dp[0][cnt][sum]) continue;
			if (sum - a[mx1] <= a[mx1]) continue;
			if ((all - sum) - a[mx2] <= a[mx2]) continue;
			chkmin(ans, abs(sum - (all - sum)));
		}
	}
	return ans;
}

int ans;

void calc() {
	ans = INF;
	sort(a, a + n);
	for (int i = 0; i < n - 1; i++) {
		chkmin(ans, calc(i, n - 1));
	}
	if (ans == INF) {
		ans = -1;
	}
}

void run() {
	calc();
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