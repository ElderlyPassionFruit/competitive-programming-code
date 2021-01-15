#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
vector<pair <int, int> > g[MAXN];
int n;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int len) {
	h[v] = len;
	tin[v] = timer++;
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
int sz[MAXN], par[MAXN];
int centr;

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
			if (sz[i.first] > sz[u]) 
				fsz = size - sz[u];
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

struct event{
	int dist, col, time;
};

vector<event> fans[MAXN];

void make() {
	dfs_lca(0, 0, 0);
	build(0, -1, n);
}

void add(int v, int d, int c, int it) {
	int u = v;
	while (u != -1) {
		int help = d - dist(v, u);
		while (!fans[u].empty() && fans[u].back().dist <= help)
			fans[u].pop_back();
		fans[u].push_back({help, c, it});
		u = par[u];
	}
}

int get_ans(int v) {
	int u = v;
	int ans = 0;
	int t = -1;
	while (u != -1) {
		int d = dist(u, v);
		if (fans[u].empty() || fans[u][0].dist < d) {
			u = par[u];
			continue;
		}
		int l = 0, r = fans[u].size();
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (fans[u][mid].dist >= d)
				l = mid;
			else
				r = mid;
		}
		if (fans[u][l].time > t) {
			ans = fans[u][l].col;
			t = fans[u][l].time;
		}
		u = par[u];
	}
	return ans;
}

vector<int> ans;

void run() {
	make();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int v, d, c;
			cin >> v >> d >> c;
			v--;
			add(v, d, c, i);
		}
		if (type == 2) {
			int v;
			cin >> v;
			v--;
			ans.push_back(get_ans(v));
		}
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