#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 110;
int n, m, d;
string t;
string s;

bool dp[MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> d >> t >> s;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j] = false;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (s[0] == t[i]) {
			dp[0][i] = true;
			ans = 1;
		}
	}
	for (int i = 1; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = max(0, j - d); k <= min(n - 1, j + d); k++) {
				if (dp[i - 1][k] && s[i] == t[j]) {
					dp[i][j] = true;
					ans = i + 1;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}