#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int u, v;
	edge() {}
	edge(int a, int b) {
		u = a;
		v = b;
		if (u > v) swap(u, v);
	}
};

bool operator<(const edge & a, const edge & b) {
	return tie(a.u, a.v) < tie(b.u, b.v);
}

const int MAXN = 1e5 + 10;
int n, root;
vector<int> g[MAXN];

map<edge, int> cnt;

void read() {
	cin >> n >> root;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		if (u == v) continue;
		cnt[edge(u, v)]++;
		if (cnt[edge(u, v)] == 1) {
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}
}


bool used[MAXN];
int tin[MAXN], up[MAXN], timer = 0;
set<edge> bridges;

void add_edge(int u, int v) {
	if (cnt[edge(u, v)] > 1) return;
	bridges.insert(edge(u, v));
}

void dfs_bridges(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) {
			chkmin(up[v], tin[i]);
		}
		else {
			dfs_bridges(i, v);
			chkmin(up[v], up[i]);
			if (tin[v] < up[i]) {
				add_edge(v, i);
			}
		}
	}
}

void clear() {
	for (int i = 0; i < n; i++)
		used[i] = false;
}

bool check(int u, int v) {
	return bridges.count(edge(u, v));
}

int color[MAXN];
int V[MAXN];
void dfs_color(int v, int c) {
	color[v] = c;
	V[c] = v;
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i]) continue;
		if (check(i, v)) continue;
		dfs_color(i, c);
	}
}

int c = 0;

void build() {
	clear();
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_bridges(i, -1);
		}
	}
	clear();
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_color(i, c++);
		}
	}
	clear();
	for (int i = 0; i < n; i++) {
		g[i].clear();
	}
	for (auto i : bridges) {
		int u = color[i.u];
		int v = color[i.v];
		assert(u != v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < c; i++) {
		sort(all(g[i]));
		g[i].resize(unique(all(g[i])) - g[i].begin());
	}
}

vector<edge> ans;

void solve() {
	for (int i = 0; i < c; i++) {
		if (i == color[root]) continue;
		if (g[i].size() > 1) continue;
		ans.push_back({root, V[i]});
	}
}

void run() {
	build();
	solve();
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i.u << " " << i.v << "\n";
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