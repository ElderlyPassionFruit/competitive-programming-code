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

int binpow(int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) {
			ans = mul(ans, a);
		}
		a = mul(a, a);
		n >>= 1;
	}
	return ans;
}

const int inv2 = binpow(2, MOD - 2);

const int MAXN = 250;

int cnk[MAXN][MAXN];

void precalcCnk() {
	cnk[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			cnk[i][j] = cnk[i - 1][j];
			if (j > 0) cnk[i][j] = add(cnk[i][j], cnk[i - 1][j - 1]);
		} 
	}
}

int dp[MAXN][MAXN][2];

void calcDp() {
	dp[1][0][0] = 1;
	for (int n = 2; n < MAXN; n++) {
		for (int k = 0; k <= n / 2; k++) {
			// one child
			dp[n][k][0] = dp[n][k][1] = 0;
			for (int used = 0; used <= 1; used++) {
				if (k - used >= 0) {
					dp[n][k][used] = add(dp[n][k][used], mul(n - 1, dp[n - 1][k - used][used ^ 1]));
				}
			}

			// two children
			for (int szL = 1; szL + 1 < n; szL++) {
				int szR = n - 1 - szL;
				assert(szL > 0 && szR > 0);
				int fmul = mul(cnk[n - 1][szL], mul(szL, szR));
				
				// used == 0
				for (int cntL = 0; cntL <= min(k, szL / 2); cntL++) {
					int cntR = k - cntL;
					if (tie(szL, cntL) <= tie(szR, cntR)) {
						int x = tie(szL, cntL) == tie(szR, cntR) ? mul(inv2, fmul) : fmul;
						dp[n][k][0] = add(
							dp[n][k][0], 
							mul(x, mul(dp[szL][cntL][1], dp[szR][cntR][1]))
							);
					}
				}

				// used == 1
				for (int cntL = 0; cntL <= min(k, szL / 2); cntL++) {
					int cntR = k - cntL - 1;
					if (cntR < 0) continue;				
					// one free
					dp[n][k][1] = add(
						dp[n][k][1],
						mul(fmul, mul(dp[szL][cntL][0], dp[szR][cntR][1]))
						);

					// both free
					if (tie(szL, cntL) <= tie(szR, cntR)) {
						int x = tie(szL, cntL) == tie(szR, cntR) ? mul(inv2, fmul) : fmul;
						dp[n][k][1] = add(
							dp[n][k][1],
							mul(x, mul(dp[szL][cntL][0], dp[szR][cntR][0]))
							);
					}
				}
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	precalcCnk();
	calcDp();
	int n, k;
	cin >> n >> k;
	cout << add(dp[n][k][0], dp[n][k][1]) << endl;
	return 0;
}