#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 228, MAXLOG = 21;

int n;
vector<int> g[MAXN];
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (auto i : g[v]) {
		h[i] = h[v] + 1;
		dfs(i, v);
	}
	tout[v] = timer++;
}

bool isUpper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (isUpper(v, u)) return v;
	if (isUpper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!isUpper(dp[v][i], u)) {
			v = dp[v][i];
		}
	}
	return dp[v][0];
}

int dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

int q;
vector<int> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	n = 4;
	g[0] = {1, 2, 3};
	cin >> q;
	for (int i = 0; i < q; i++) {
		int v;
		cin >> v;
		v--;
		a.push_back(n);
		g[v].push_back(n++);
		g[v].push_back(n++);
	}
	dfs(0, 0);
	int ans = 2;
	int v1 = 1;
	int v2 = 2;
	for (auto x : a) {
		int u1 = x;
		int u2 = x + 1;
		if (dist(u1, v1) > ans) {
			v2 = u1;
			ans = dist(v1, v2);
		}
		if (dist(u1, v2) > ans) {
			v1 = u1;
			ans = dist(v1, v2);
		}
		if (dist(u2, v1) > ans) {
			v2 = u2;
			ans = dist(v1, v2);
		}
		if (dist(u2, v2) > ans) {
			v1 = u2;
			ans = dist(v1, v2);
		}
		cout << ans << "\n";
	}
	return 0;
}