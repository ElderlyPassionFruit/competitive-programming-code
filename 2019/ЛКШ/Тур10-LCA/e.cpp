#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n, m, f;

vector<int> g[MAXN];
bool used[MAXN];

int t[MAXN], up[MAXN];
int timer = 0;

set<pair <int, int> > bridges;
int color[MAXN];

set<int> gr[MAXN];
int tin[MAXN], tout[MAXN], h[MAXN];
int dp[MAXN][MAXLOG];

pair <int, int> ed(int a, int b) {
	if (a > b)
		swap(a, b);
	return make_pair(a, b);
}

void is_bridge(int a, int b) {
	bridges.insert(ed(a, b));
}

void dfs(int v, int p) {
	used[v] = true;
	t[v] = up[v] = timer++;
	for (auto i : g[v]) {
		if (i == p)
			continue;
		if (used[i]) {
			chkmin(up[v], t[i]);
		}
		else {
			dfs(i, v);
			chkmin(up[v], up[i]);
			if (up[i] > t[v]) {
				is_bridge(i, v);
			}
		}
	}
}

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : gr[v]) {
		if (i != p) {
			dfs_lca(i, v, len);
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
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	}
	return dp[v][0];
}

void dfs_color(int v, int col) {
	used[v] = true;
	color[v] = col;
	for (auto i : g[v]) {
		if (!used[i] && bridges.find(ed(i, v)) == bridges.end())
			dfs_color(i, col);
	}
}

void make() {
	dfs(f, f);
	for (int i = 0; i < n; i++)
		used[i] = 0;
	timer = 0;
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_color(i, c++);
		}
	}
	
	for (int i = 0; i < n; i++)
		used[i] = 0;

	for (auto i : bridges) {
		if (color[i.first] != color[i.second]) {
			gr[color[i.first]].insert(color[i.second]);
			gr[color[i.second]].insert(color[i.first]);
		}
	}

	dfs_lca(color[f], color[f], 0);
}

void read() {
	cin >> n >> m;
	cin >> f;
	f--;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

vector<int> ans;

void run() {
	make();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		a = color[a];
		b = color[b];
		int fans = h[lca(a, b)];
		ans.push_back(fans);
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