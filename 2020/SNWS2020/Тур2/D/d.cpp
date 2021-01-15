#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, m;
int v[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

struct edge{
	int u, v;
	edge() {}
	edge(int a, int b) {
		u = a, v = b;
		if (u > v)
			swap(v, u);
	}
};

bool operator<(const edge & a, const edge & b) {
	return tie(a.u, a.v) < tie(b.u, b.v);
}

set<edge> bridges;

void add_bridge(int u, int v) {
	bridges.insert(edge(u, v));
}

int tin[MAXN], up[MAXN], used[MAXN];
int timer = 0;

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
			if (tin[v] < up[i]) 
				add_bridge(v, i);
		}
	}
}

bool check(int v, int u) {
	return bridges.count(edge(v, u));
}

int color[MAXN];

void dfs_color(int v, int c) {
	color[v] = c;
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i]) continue;
		if (check(v, i)) continue;
		dfs_color(i, c);
	}
}

int w[MAXN];

void build() {
	for (int i = 0; i < n; i++)
		used[i] = false;
	dfs_bridges(0, -1);
	for (int i = 0; i < n; i++)
		used[i] = false;
	int c = 0;
	for (int i = 0; i < n; i++)
		if (!used[i])
			dfs_color(i, c++);
	for (int i = 0; i < n; i++) {
		g[i].clear();
		w[i] = 0;
	}

	/*cout << "color = " << endl;
	for (int i = 0; i < n; i++) {
		cout << color[i] << " ";
	}
	cout << endl;*/
	for (int i = 0; i < n; i++) {
		w[color[i]] += v[i];
	}

	/*cout << "w = " << endl;
	for (int i = 0; i < n; i++)
		cout << w[i] << " ";
	cout << endl;*/
	for (auto i : bridges) {
		int u = color[i.u];
		int v = color[i.v];
		assert(u != v);
		g[u].push_back(v);
		g[v].push_back(u); 
	}
	n = c;
	for (int i = 0; i < n; i++) {
		sort(all(g[i]));
		g[i].resize(unique(all(g[i])) - g[i].begin());
	}
}

int dp[MAXN][2];

void dfs_calc(int v, int p) {
	dp[v][0] = dp[v][1] = 0;
	int mx1 = 0, mx2 = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_calc(i, v);
		if (dp[i][0] > mx2) {
			mx2 = dp[i][0];
			if (mx1 < mx2)
				swap(mx1, mx2);
		}
	}
	dp[v][0] = w[v] + mx1;
	dp[v][1] = w[v] + mx1 + mx2;
}

void calc() {
	dfs_calc(0, 0);
}

int ans;

void make_ans() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		chkmax(ans, dp[i][0]);
		chkmax(ans, dp[i][1]);
	}
}

void run() {
	build();
	calc();
	make_ans();
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