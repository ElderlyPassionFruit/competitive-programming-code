#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n, maxL, maxW;
vector<pair<int, int> > g[MAXN];

int dp[MAXN][MAXLOG], h[MAXN], w[MAXN], tin[MAXN], tout[MAXN], timer = 0;

void dfs_lca(int v, int p, int len, int W) {
	tin[v] = timer++;
	h[v] = len++;
	w[v] = W;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i.first != p) {
			dfs_lca(i.first, v, len, W + i.second);
		}
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

int get_dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

int get_w(int v, int u) {
	return w[v] + w[u] - 2 * w[lca(v, u)];
}

void read() {
	cin >> n >> maxL >> maxW;
	for (int i = 1; i < n; i++) {
		int p, w;
		cin >> p >> w;
		p--;
		g[i].push_back({p, w});
		g[p].push_back({i, w});
	}
}

int ans = 0;

void run() {
	dfs_lca(0, 0, 0, 0);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int haveL = get_dist(i, j);
			int haveW = get_w(i, j);
			if (haveL <= maxL && haveW <= maxW)
				ans++;
		}
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}