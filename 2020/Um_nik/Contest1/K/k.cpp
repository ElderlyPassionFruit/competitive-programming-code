#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 2e3 + 10;
int n, k;
string s;
int dp[MAXN][MAXN];
int pref[MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k >> s;
	dp[0][0] = 1;
	pref[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int sum = 0; sum <= k; sum++) {
			// calc t[i] < s[i]
			dp[i][sum] = add(dp[i][sum], mul(pref[i - 1][sum], s[i - 1] - 'a'));
			// calc t[i] > s[i]
			for (int pref = 0; sum - (pref + 1) * (n - i + 1) >= 0 && pref < i; pref++) {
				dp[i][sum] = add(dp[i][sum], mul(dp[i - pref - 1][sum - (pref + 1) * (n - i + 1)], 'z' - s[i - 1]));
			}
			pref[i][sum] = add(pref[i][sum], pref[i - 1][sum]);
			pref[i][sum] = add(pref[i][sum], dp[i][sum]);
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		ans = add(ans, dp[i][k]);
	}
	cout << ans << endl;
	return 0;
}