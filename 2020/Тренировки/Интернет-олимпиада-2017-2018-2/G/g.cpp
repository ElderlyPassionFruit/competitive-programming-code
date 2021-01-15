#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct fdp{
	int ans, val;
	fdp() {}
	fdp(int _ans, int _val) {
		ans = _ans, val = _val;
	}
};

bool operator<(const fdp & a, const fdp & b) {
	return tie(a.ans, a.val) < tie(b.ans, b.val);
}

const fdp INF = fdp(1e9 + 228 + 1337, 1e9 + 228 + 1337);

const int MAXN = 20;
int n;
int a[MAXN];
fdp dp[MAXN][MAXN];

void chkmin(fdp & x, fdp y) {
	if (y < x) x = y;
}

void solve(int k) {
	dp[0][0] = {0, 0};
	for (int len = 1; len <= n; len++) {
		for (int cnt = 0; cnt <= k; cnt++) {
			dp[len][cnt] = INF;
			chkmin(dp[len][cnt], fdp(dp[len - 1][cnt].ans + 1, dp[len - 1][cnt].val));
			if (cnt == 0) {
				chkmin(dp[len][cnt], fdp(dp[len - 1][k].ans + 1, 0));
				continue;
			}
			if (a[len] > dp[len - 1][cnt - 1].val) {
				chkmin(dp[len][cnt], fdp(dp[len - 1][cnt - 1].ans, a[len]));
			}
			if (cnt == 1) {
				chkmin(dp[len][cnt], fdp(dp[len - 1][k].ans, a[len]));
			}
			if (cnt != k) continue;
			if (a[len] > dp[len - 1][k].val) {
				chkmin(dp[len][cnt], fdp(dp[len - 1][cnt].ans, a[len]));
			}
		}
	}
	cout << "k = " << k << endl;
	cout << "dp = " << endl;
	for (int len = 1; len <= n; len++) {
		cout << "len = " << len << endl;
		for (int cnt = 0; cnt <= k; cnt++) {
			cout << dp[len][cnt].ans << " " << dp[len][cnt].val << endl;
		}
	}
	int ans = 0;
	if (dp[n][k].ans != INF.ans) ans = max(ans, n - dp[n][k].ans);
	if (dp[n][0].ans != INF.ans) ans = max(ans, n - dp[n][0].ans);
	cout << ans << " ";
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = INF;
	solve(3);

	for (int i = 1; i <= n; i++) {
		solve(i);
	}
	cout << endl;
	return 0;
}

/*
WA 415
input = 
10
1 5 1 6 4 2 9 6 3 6 

ans =  10 8 6 4 0 0 0 0 0 0 

out =  10 8 4 4 0 0 0 0 0 0 


*/