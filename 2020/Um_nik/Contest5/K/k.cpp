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

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 1e3 + 10;
int dp[MAXN];
int n;
int p[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for (int i = 2; i <= n + 1; i++) {
		dp[i] = add(mul(2, dp[i - 1]), sub(2, dp[p[i - 1]]));
	}
	cout << dp[n + 1] << endl;
	return 0;
}