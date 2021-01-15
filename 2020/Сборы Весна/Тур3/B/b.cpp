#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
struct edge{
	int to, ind;
	edge() {}
	edge(int _to, int _ind) {
		to = _to, ind = _ind;
	}
};

const int MAXN = 2e5, MAXLOG = 17;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;
int n;
vector<pair<int, int>> g[MAXN];
pair<int, int> cost[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		g[a].push_back({b, i});
		g[b].push_back({a, i});
		cost[i] = {c, d};
	}
}

void dfs_lca(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto [to, ind] : g[v]) {
		if (to == p) continue;
		dfs_lca(to, v);
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

void build() {
	dfs_lca(0, 0);
}

ll ans;

int add[MAXN];

void add_vertical_path(int up, int down) {
	if (up == down) return;
	add[down]++;
	add[up]--;
}

void add_path(int u, int v) {
	int l = lca(u, v);
	add_vertical_path(l, u);
	add_vertical_path(l, v);
}

int cnt[MAXN];

void dfs_calc(int v, int p) {
	int ind_par = -1;
	for (auto [to, ind] : g[v]) {
		if (to == p) {
			ind_par = ind;
			continue;
		}
		dfs_calc(to, v);
		add[v] += add[to];
	}
	if (ind_par == -1) return;
	cnt[ind_par] = add[v];
} 

void calc() {
	for (int i = 0; i < n - 1; i++) {
		add_path(i, i + 1);
	}
	dfs_calc(0, 0);
	ans = 0;
	for (int i = 0; i < n - 1; i++) {
		ans += min((ll) cost[i].first * cnt[i], (ll)cost[i].second);
	}
}

void run() {
	build();
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