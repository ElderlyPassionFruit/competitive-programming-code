#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10, MAXLOG = 22;
vector<pair <int, int> > g[MAXN];
int n;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i.first != p) {
			dfs_lca(i.first, v, len + i.second);
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

int dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

bool used[MAXN];
int par[MAXN], sz[MAXN], centr;

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int m = 0;
	for (auto i : g[v]) {
		if (i.first != p && !used[i.first]) {
			dfs_centr(i.first, v, size);
			sz[v] += sz[i.first];
			chkmax(m, sz[i.first]);
		}
	}
	chkmax(m, size - sz[v]);
	if (m <= size / 2) {
		centr = v;
	}
}
 
void build(int v, int p, int size) {
	dfs_centr(v, v, size);
	int u = centr;
	used[u] = true;
	par[u] = p;
	for (auto i : g[u]) {
		if (!used[i.first]) {
			int fsz = sz[i.first];
			if (fsz > sz[u]) {
				fsz = size - sz[u];
			}
			build(i.first, u, fsz);
		}
	}
}

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, l;
		cin >> u >> v >> l;
		u--;
		v--;
		g[u].push_back({v, l});
		g[v].push_back({u, l});
	}
}

void make() {
	dfs_lca(0, 0, 0);
	build(0, -1, n);
}

set<pair <int, int> > fans[MAXN];

void add(int v) {
	int u = v;
	while (u != -1) {
		int d = dist(u, v);
		fans[u].insert({d, v});
		u = par[u];
	}
}

void del(int v) {
	int u = v;
	while (u != -1) {
		int d = dist(u, v);
		fans[u].erase({d, v});
		u = par[u];
	}
}

const int INF = 1e9 + 10;

int get_ans(int v) {
	int ans = INF;
	int u = v;
	while (u != -1) {
		if (fans[u].empty()) {
			u = par[u];
			continue;
		}
		int d1 = dist(u, v);
		int d2 = fans[u].begin()->first;
		chkmin(ans, d1 + d2);
		u = par[u];
	}
	return ans;
}

vector<int> ans;
void run() {
	make();
	int q;
	cin >> q;
	add(0);
	for (int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			int v;
			cin >> v;
			v--;
			add(v);
		}
		if (type == '-') {
			int v;
			cin >> v;
			v--;
			del(v);
		}
		if (type == '?') {
			int v;
			cin >> v;
			v--;
			ans.push_back(get_ans(v));
		}
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
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