#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

struct edge{
	int to, ind;
	edge() {}
	edge(int _to, int _ind) {
		to = _to, ind = _ind;
	}
};

const int MAXN = 1e5 + 10, MAXLOG = 17;
int n, m, p;
vector<edge> g[MAXN];
vector<pair<int, int>> ed;
map<pair<int, int>, int> cnt;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ed.push_back({u, v});
		cnt[{min(u, v), max(u, v)}]++;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
}

set<int> bridges;
bool used[MAXN];
int tin[MAXN], up[MAXN], timer = 0;

void dfs_bridges(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto [to, ind] : g[v]) {
		if (to == p) continue;
		if (used[to]) {
			chkmin(up[v], tin[to]);
		}
		else {
			dfs_bridges(to, v);
			chkmin(up[v], up[to]);
			if (up[to] > tin[v] && cnt[{min(to, v), max(to, v)}] < 2) {
				bridges.insert(ind);
			}
		}
	}
}

int color[MAXN];

void dfs_color(int v, int c) {
	color[v] = c;
	for (auto [to, ind] : g[v]) {
		if (color[to] != -1) continue;
		if (bridges.count(ind)) continue;
		dfs_color(to, c);
	}
}

vector<edge> gr[MAXN];
int tout[MAXN], dp[MAXN][MAXLOG];
int Ind[MAXN], h[MAXN];

void dfs_lca(int v, int p, int len) {
	used[v] = true;
	tin[v] = timer++;
	dp[v][0] = p;
	h[v] = len++;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto [i, ind] : gr[v]) {
		if (i != p) {
			Ind[i] = ind;
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
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

string ans;

int par[MAXN], sz[MAXN], fans[MAXN];

void make() {
	for (int i = 0; i < MAXN; i++)
		par[i] = i, sz[i] = 1, fans[i] = i;
}

int get_par(int v) {
	if (v == par[v]) return v;
	return par[v] = get_par(par[v]);
}

void uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	if (sz[a] > sz[b]) swap(a, b);
	par[b] = a;
	if (h[fans[a]] > h[fans[b]])
		fans[a] = fans[b];
}

void build() {
	make();
	ans = "";
	for (int i = 0; i < m; i++) {
		ans += "B";
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_bridges(i, -1);
		}
	}
	for (int i = 0; i < n; i++) color[i] = -1;
	
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			dfs_color(i, c++);
		}
	}
	
	for (auto i : bridges) {
		int u = color[ed[i].first];
		int v = color[ed[i].second];
		assert(u != v);
		gr[u].push_back({v, i});
		gr[v].push_back({u, i});
	}
	
	for (int i = 0; i < c; i++) {
		used[i] = false;
	}
	for (int i = 0; i < c; i++) {
		if (!used[i]) {
			dfs_lca(i, i, 0);
		}
	}
}

void no() {
	cout << "-1" << endl;
	exit(0);
}

void make(int u, int v, int ind) {
	if (color[ed[ind].first] == u && color[ed[ind].second] == v) {
		if (ans[ind] == 'L') no();
		ans[ind] = 'R';
	}
	else {
		if (ans[ind] == 'R') no();
		ans[ind] = 'L';
	}
}

void upd(int s, int f) {
	int v = color[s];
	int u = color[f];
	if (v == u) return;
	s = v;
	f = u;
	while (!is_upper(v, f)) {
		make(v, dp[v][0], Ind[v]);
		uni(v, dp[v][0]);
		v = fans[get_par(v)];
	}
	while (!is_upper(u, s)) {
		make(dp[u][0], u, Ind[u]);
		uni(u, dp[u][0]);
		u = fans[get_par(u)];
	}
}

void run() {
	build();
	cin >> p;
	while (p--) {
		int s, f;
		cin >> s >> f;
		s--;
		f--;
		upd(s, f);
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