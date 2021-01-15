#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10, MAXLOG = 17;
int n, k;
int c[MAXN];
vector<int> g[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		c[i]--;
	}
}

/*
int par[MAXN], sz[MAXN];

void make() {
	for (int i = 0; i < k; i++) {
		par[i] = i, sz[i] = 1;
	}
}

int get_par(int v) {
	if (v == par[v]) return v;
	return par[v] = get_par(par[v]);
}

void uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	par[b] = a;
	sz[a] += sz[b];
}
*/

struct segment{
	int l, r, color;
	segment() {}
	segment(int _l, int _r, int _color) {
		l = _l, r = _r, color = _color;
	}
};

int last[MAXN], tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], h[MAXN], timer = 0;
vector<segment> have;

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

void add(int u, int v, int color) {
	if (u == v) return;
	if (tin[u] > tin[v]) swap(u, v);
	if (is_upper(u, v)) {
		have.push_back({tin[u], tin[v], color});
		return;
	}
	int l = lca(u, v);
	have.push_back({l, u, color});
	have.push_back({l, v, color});
}

void dfs_lca(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_lca(i, v);
	}

	tout[v] = timer++;
}

void dfs(int v, int p) {
	if (last[c[v]] != -1) {
		add(last[c[v]], v, c[v]);
	}
	last[c[v]] = v;

	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v);
		last[c[v]] = v;
	}
}

void build() {
	for (int i = 0; i < k; i++)
		last[i] = -1;
	dfs_lca(0, 0);	
	dfs(0, 0);
}

bool check(int l, int r, int x) {
	return l <= x && x <= r;	
}

bool check(segment a, segment b) {
	return check(a.l, a.r, b.l) || check(a.l, a.r, b.r);
}

vector<int> gr[MAXN];

vector<int> order;
vector<bool> used;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : gr[v]) {
		if (used[i]) continue;
		dfs_order(i);
	}
	order.push_back(v);
}

vector<int> cnt;
vector<int> color;

void dfs_color(int v, int c) {
	cnt[cnt.size() - 1]++;
	color[v] = c;
	used[v] = true;
	for (auto i : gr[v]) {
		if (used[i]) continue;
		dfs_color(i, c);
	} 
}

int ans;

void calc() {
	for (int i = 0; i < have.size(); i++) {
		for (int j = i + 1; j < have.size(); j++) {
			if (have[i].color == have[j].color) continue;
			if (check(have[i], have[j])) gr[have[i].color].push_back(have[j].color);
			if (check(have[j], have[i])) gr[have[j].color].push_back(have[i].color);
		}
	}

	cout << "gr = " << endl;

	used.assign(k, false);
	for (int i = 0; i < k; i++) {
		if (used[i]) continue;
		dfs_order(i);
	}
	reverse(all(order));
	used.assign(k, false);
	color.assign(k, 0);
	int c = 0;
	for (int i = 0; i < k; i++) {
		if (used[i]) continue;
		cnt.push_back(0);
		dfs_color(i, c++);
	}

	vector<bool> good(c, true);
	for (int i = 0; i < k; i++) {
		for (auto j : gr[i]) {
			int u = color[i], v = color[j];
			if (u == v) continue;
			good[v] = false;
		}
	}
	ans = k - 1;
	for (int i = 0; i < c; i++) {
		if (good[i]) {
			chkmin(ans, cnt[i]);
		}
	}
}

void run() {
	//make();
	build();
	cout << "tin = " << endl;
	for (int i = 0; i < n; i++)
		cout << tin[i] << " ";
	cout << endl;
	cout << "have = " << endl;
	for (auto i : have) {
		cout << i.l << " " << i.r << " " << i.color << endl;
	}
	calc();
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