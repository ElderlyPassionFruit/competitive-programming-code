#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void chkmin(int & x, const int y) {
	if (y < x) x = y;
}

int n, m, e;
const int MAXM = 310;
const int MAXN = 10;
const int INF = 1e9 + 10;
int dist[MAXM][MAXM];
int have[MAXM];

int dp[MAXM][1 << MAXN];

int get(int mask) {
	return __builtin_popcount(mask);
}

bool check(int mask) {
	int x = get(mask);
	for (int i = 0; i < x; i++) {
		if ((mask >> i) & 1) continue;
		return false;
	}
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> e;
	for (int i = 0; i < m; i++) {
		cin >> have[i];
	}
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	
	for (int i = 0; i < e; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		chkmin(dist[u][v], cost);
	} 

	for (int k = 0; k < m; k++) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				if (dist[i][k] == INF || dist[k][j] == INF) continue;
				chkmin(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < (1 << n); j++) {
			dp[i][j] = INF;
		}
	}

	for (int i = 0; i < m; i++) {
		if (have[i] == 0) {
			dp[i][1 << have[i]] = 0;
		}
	}
	int ans = INF;

	for (int mask = 2; mask < (1 << n); mask++) {
		if (!check(mask)) continue;
		int now = get(mask);
		for (int i = 0; i < m; i++) {
			if (have[i] != now - 1) continue;
			for (int j = 0; j < m; j++) {
				if (have[j] != now - 2) continue;
				chkmin(dp[i][mask], dp[j][mask ^ (1 << have[i])] + dist[j][i]);
			}
		}
	}
	
	for (int i = 0; i < m; i++) {
		chkmin(ans, dp[i][(1 << n) - 1]);
	}

	if (ans == INF) {
		ans = -1;
	}
	cout << ans << endl;
	return 0;
}