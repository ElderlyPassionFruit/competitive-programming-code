#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
int dp[MAXN][MAXN];
int a[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
} 
	
int pref[MAXN];

void build() {
	pref[0] = 0;
	for (int i = 1; i <= n; i++)
		pref[i] = pref[i - 1] + a[i];
}

const int INF = 1e18;
int ans;

void calc() {
	int sum = pref[n];
	int norm = sum / n;
	int cnt = sum % n;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j] = INF;

	dp[0][0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= min(i, cnt); j++) {
			int add = abs(pref[i] - (norm * i + j));
			dp[i][j] = dp[i - 1][j];
			if (j > 0)
				chkmin(dp[i][j], dp[i - 1][j - 1]);
			dp[i][j] += add;
		}
	}
	ans = min(dp[n - 1][cnt], (cnt > 0 ? dp[n - 1][cnt - 1] : INF));
}

void run() {
	build();
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