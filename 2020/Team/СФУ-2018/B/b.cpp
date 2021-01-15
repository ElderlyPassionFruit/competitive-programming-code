#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 110;
const int MAXT = 10110;
const int INF = 2e9 + 228 + 1337;

int dp[MAXN][MAXT];
int par[MAXN][MAXT];
int n, t;
int s[MAXN], c[MAXN], k[MAXN];

void relax(int pos, int val, int cost, int add) {
	if (val > t + 100) return;
	if (dp[pos][val] <= cost) return;
	dp[pos][val] = cost;
	par[pos][val] = add;
}

int ans;
int fans[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> t;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> c[i] >> k[i];
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXT; j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;

	for (int i = 0; i < n; i++) {
		for (int now = 0; now <= t + 100; now++) {
			if (dp[i][now] == INF) continue;
			relax(i + 1, now, dp[i][now], 0);
			int x = k[i] * c[i];
			for (int add = k[i], cost = s[i] + x; add <= 100; add += k[i], cost += x) {
				relax(i + 1, now + add, dp[i][now] + cost, add);
			}		
		}
	}

	int now = t;
	for (int i = t; i <= t + 100; i++) {
		if (dp[n][now] <= dp[n][i]) continue;
		now = i;
	}

	//assert(dp[n][now] != INF);

	ans = dp[n][now];
	for (int i = n; i >= 1; i--) {
		fans[i] = par[i][now];
		now -= fans[i];
	}

	cout << ans << endl;
	for (int i = 1; i <= n; i++) {
		cout << fans[i] << " ";
	}
	cout << endl;
	return 0;
}