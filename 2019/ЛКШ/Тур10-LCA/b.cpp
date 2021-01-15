#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n;
vector<pair <int, int> > g[MAXN];
int dp[MAXN][MAXLOG], m[MAXN][MAXLOG], tin[MAXN], tout[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int cost) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	
	m[v][0] = cost;
	for (int i = 1; i < MAXLOG; i++) 
		m[v][i] = min(m[v][i - 1], m[dp[v][i - 1]][i - 1]);

	for (auto i : g[v])
		if (i.first != p)
			dfs_lca(i.first, v, i.second);
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

int get_path(int v, int u) {
	int ans = 1e9 + 10;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u)) {
			chkmin(ans, m[v][i]);
			v = dp[v][i];
		}
	}
	if (v != u)
		chkmin(ans, m[v][0]);
	return ans;
}

int get_min(int v, int u) {
	int l = lca(v, u);
	return min(get_path(v, l), get_path(u, l));
}

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int v, cost;
		cin >> v >> cost;
		v--;
		g[v].push_back({i, cost});
		g[i].push_back({v, cost});
	}
}

vector<int> ans;
void run() {
	dfs_lca(0, 0, 1e9 + 10);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ans.push_back(get_min(u, v));
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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