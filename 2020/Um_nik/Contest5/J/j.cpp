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

const int MAXK = 2e3 + 10;

int cnk[MAXK][MAXK];
int fact[MAXK];

void initFacts() {
	fact[0] = 1;
	for (int i = 1; i < MAXK; i++) {
		fact[i] = mul(i, fact[i - 1]);
	}
	cnk[0][0] = 1;
	for (int i = 1; i < MAXK; i++) {
		cnk[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			cnk[i][j] = add(cnk[i - 1][j - 1], cnk[i - 1][j]);
		}
	}
}

const int MAXN = 1001;
int dp[2][MAXN][MAXN];
int fans[MAXN][MAXN];
int pref[2][MAXN][MAXN];

void calcDp() {
	for (int sum = 1; sum < MAXN; sum++) {
		dp[0][sum][sum] = 1;
		fans[1][sum] = add(fans[1][sum], 1);
	}
	for (int i = 2; i <= 50; i++) {
		for (int sum = i * (i + 1) / 2; sum < MAXN; sum++) {
			for (int lastVal = 1; sum / lastVal >= i; lastVal++) {
				if (lastVal + 1 > sum - lastVal) continue;
				for (int prevVal = lastVal + 1; prevVal <= sum - lastVal; prevVal++) {
					dp[1][sum][lastVal] = add(dp[1][sum][lastVal], dp[0][sum - lastVal][prevVal]);
				}
				//dp[1][sum][lastVal] = add(dp[1][sum][lastVal], sub(pref[1][sum - lastVal][sum - lastVal], pref[1][sum - lastVal][lastVal]));
				fans[i][sum] = add(fans[i][sum], dp[1][sum][lastVal]);
			}
		}
		for (int sum = (i - 1) * i / 2; sum < MAXN; sum++) {
			for (int lastVal = 1; sum / lastVal >= i - 1; lastVal++) {
				dp[0][sum][lastVal] = 0;
			}
		}
		for (int sum = i * (i + 1) / 2; sum < MAXN; sum++) {
			for (int lastVal = 1; sum / lastVal >= i; lastVal++) {
				dp[0][sum][lastVal] = dp[1][sum][lastVal];
				dp[1][sum][lastVal] = 0;
			}
		}
	}
}

int mem[MAXN][MAXN];

void solve() {
	int n, k;
	cin >> n >> k;
	if (k > 50) {
		cout << 0 << "\n";
		return;
	}
	if (mem[n][k] != -1) {
		cout << mem[n][k] << "\n";
		return;
	}
	int ans = 0;
	for (int sum = 1; sum <= n; sum++) {
		ans = add(ans, mul(fans[k][sum], cnk[n - sum + k][k]));
	}
	ans = mul(ans, fact[k]);
	mem[n][k] = ans;
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	initFacts();
	calcDp();
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j <= 50; j++) {
			mem[i][j] = -1;
		}
	}
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}