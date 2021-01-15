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

const int MAXSUM = 1e4 + 1337 + 228;
const int SUM = 10010;
int n;
int dp[2][MAXSUM * 2];
int ans = 0;

void add(int x) {
	dp[0][MAXSUM] = add(dp[0][MAXSUM], 1);
	for (int sum = -SUM; sum <= SUM; sum++) {
		dp[1][sum + MAXSUM] = add(dp[0][sum - x + MAXSUM], dp[0][sum + x + MAXSUM]);
	}
	for (int sum = -SUM; sum <= SUM; sum++) {
		dp[0][sum + MAXSUM] = dp[1][sum + MAXSUM];
		dp[1][sum + MAXSUM] = 0;
	}
	ans = add(ans, dp[0][MAXSUM]);
	/*cout << "dp = " << endl;
	for (int i = -SUM; i <= SUM; i++) {
		cout << dp[0][i + MAXSUM] << " ";
	}
	cout << endl;
	cout << "ans = " << ans << endl;*/
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		add(x);
	}
	cout << ans << endl;
	return 0;
}