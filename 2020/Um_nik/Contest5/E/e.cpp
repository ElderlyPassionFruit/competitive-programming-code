#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 5e3 + 10;

int n, m;
char a[MAXN][MAXN];

int dp[MAXN][MAXN];
int have[MAXN];

int solve(int pos) {
	for (int j = 0; j < n; j++) {
		if (a[j][pos] == '1') {
			dp[j][pos] = dp[j][pos + 1] + 1;
		}
		have[j] = dp[j][pos];
	}
	sort(have, have + n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, (i + 1) * have[n - 1 - i]);
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	int ans = 0;
	for (int i = m - 1; i >= 0; i--) {
		ans = max(ans, solve(i));
	}
	cout << ans << endl;
	return 0;
}