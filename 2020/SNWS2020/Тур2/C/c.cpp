#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
pair<int, int> dp[MAXN][MAXN];

const int MOD = 998244353;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

int ans;

void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j] = {1e9, 0};
	dp[0][0] = {0, 1};
}

void calc() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (s[i] == 'm') {
				if (j == 0) {
					dp[i][j] = dp[i - 1][j];
					dp[i][j].first++;
					continue;
				}
				dp[i][j].first = min(dp[i - 1][j - 1].first, dp[i - 1][j].first + 1);
				if (dp[i][j].first == dp[i - 1][j - 1].first) {
					dp[i][j].second = add(dp[i][j].second, dp[i - 1][j - 1].second);
				}
				if (dp[i][j].first == dp[i - 1][j].first + 1) {
					dp[i][j].second = add(dp[i][j].second, dp[i - 1][j].second);
				}
			}
			else {
				if (j == n) {
					dp[i][j] = dp[i - 1][j];
					dp[i][j].first++;
					continue;
				}
				dp[i][j].first = min(dp[i - 1][j + 1].first, dp[i - 1][j].first + 1);
				if (dp[i][j].first == dp[i - 1][j + 1].first) {
					dp[i][j].second = add(dp[i][j].second, dp[i - 1][j + 1].second);
				}
				if (dp[i][j].first == dp[i - 1][j].first + 1) {
					dp[i][j].second = add(dp[i][j].second, dp[i - 1][j].second);
				}
			}
		}
	}
}

void run() {
	build();
	calc();
	cout << "s = " << s << endl;
	cout << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			cout << dp[i][j].first << ", " << dp[i][j].second << " | "; 
		}
		cout << endl;
	}
	ans = dp[n][0].second;
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