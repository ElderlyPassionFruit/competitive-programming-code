#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<pair<int, int>> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second;
}

int ans;

void run() {
	sort(all(a), [&] (pair<int, int> i, pair<int, int> j) {return i.first + i.second > j.first + j.second;});
	vector<vector<int>> dp(n + 1, vector<int> (n + 1, -1));
	dp[0][0] = 2e9 + 10;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = dp[i - 1][j];
			if (j > 0) {
				chkmax(dp[i][j], min(dp[i - 1][j - 1] - a[i - 1].first, a[i - 1].second));
			}
		}
	}
	cout << "dp = " << endl;
	for (auto i : dp) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
	ans = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (dp[i][j] >= 0) {
				chkmax(ans, j);
			}
		}
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