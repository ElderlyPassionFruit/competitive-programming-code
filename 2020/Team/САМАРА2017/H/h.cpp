#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
int n, m;
const int MAXN = 1e3 + 10;
int dp[MAXN][MAXN][4];
int a[MAXN][MAXN];
const int INF = 1e9 + 100;
void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			for (int k = 0; k < 4; k++)
				dp[i][j][k] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j][0] = a[i][j];
			dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
			dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][0]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			dp[i][j][1] = a[i][j];
			dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][1]);
			dp[i][j][1] = max(dp[i][j][1], dp[i][j + 1][1]);
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= m; j++) {
			dp[i][j][2] = a[i][j];
			dp[i][j][2] = max(dp[i][j][2], dp[i + 1][j][2]);
			dp[i][j][2] = max(dp[i][j][2], dp[i][j - 1][2]);
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = m; j >= 1; j--) {
			dp[i][j][3] = a[i][j];
			dp[i][j][3] = max(dp[i][j][3], dp[i + 1][j][3]);
			dp[i][j][3] = max(dp[i][j][3], dp[i][j + 1][3]);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	build();
	pair <int, pair<int, int> > ans = {1e9 + 10, {}};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			pair<int, pair<int, int> > fans;
			fans.first = 0;
			fans.first = max(fans.first, dp[i - 1][j - 1][0]);
			fans.first = max(fans.first, dp[i - 1][j + 1][1]);
			fans.first = max(fans.first, dp[i + 1][j - 1][2]);
			fans.first = max(fans.first, dp[i + 1][j + 1][3]);
			fans.second = {i, j};
			ans = min(ans, fans);
		}
	}
	cout << ans.second.first << " " << ans.second.second << endl;
	return 0;
}










