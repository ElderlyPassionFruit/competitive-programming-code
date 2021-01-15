#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

struct edge{
	int to, ind;
	edge() {}
	edge(int _to, int _ind) {
		to = _to, ind = _ind;
	}
};

const int MAXN = 1e6 + 10;
int n, m;
vector<edge> g[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) g[i].clear();
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
}

bool bridges[MAXN];
bool used[MAXN];
int tin[MAXN], up[MAXN];
int timer = 0;

void dfs_bridges(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto [to, ind] : g[v]) {
		if (to == p) continue;
		if (used[to]) {
			chkmin(up[v], tin[to]);
		} else {
			dfs_bridges(to, v);
			chkmin(up[v], up[to]);
			if (tin[v] < up[to]) {
				bridges[ind] = true;
			}
		}
	}
}

int ans;
int f[MAXN];

void build() {
	ans = 0;
	fill(used, used + n, false);
	fill(bridges, bridges + m, false);
	dfs_bridges(0, 0);
	f[0] = 1;
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = add(f[i - 1], mul(f[i - 2], i - 1));
	}
}

int dp[MAXN];
int sz[MAXN];
void dfs_calc(int v, int p) {
	used[v] = true;
	int fans = 1;
	int cnt = 0;
	sz[v] = 1;
	for (auto [to, ind] : g[v]) {
		if (to == p) continue;
		if (!bridges[ind]) continue;
		dfs_calc(to, v);
		sz[v] += sz[to];
		fans = mul(fans, dp[to]);
		cnt++;
	}
	dp[v] = 0;
	dp[v] = add(dp[v], mul(fans, f[cnt]));
	if (v != p) {
		dp[v] = add(dp[v], mul(fans, mul(cnt, f[cnt - 1])));
	}
}

void calc() {
	dfs_calc(0, 0);
	fill(used, used + n, false);
	ans = 1;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_calc(i, i);
			flag |= sz[i] > 1;
			ans = mul(ans, dp[i]);		
		}
	}
}

vector<pair<int, int>> ed;
int par[MAXN];
int Ind[MAXN];
int h[MAXN];
void dfs_check(int v, int p, int len) {
	used[v] = true;
	par[v] = p;
	h[v] = len++;
	for (auto [to, ind] : g[v]) {
		if (to == p) {
			Ind[v] = ind;
			continue;
		}
		if (!used[to]) {
			dfs_check(to, v, len);
		}
		else if (h[to] < h[v]) {
			ed.push_back({to, v});
		}
	}
}

int sum[MAXN];

bool check() {
	fill(used, used + n, false);
	fill(Ind, Ind + n, -1);
	fill(h, h + n, 0);
	ed.clear();
	dfs_check(0, -1, 0);
	fill(sum, sum + m, 0);
	for (auto i : ed) {
		int to = i.first, v = i.second;
		while (to != v) {
			sum[Ind[v]]++;
			if (sum[Ind[v]] > 1) return false;
			v = par[v];
		}
	}
	return true;
}

void run() {
	build();
	calc();
}

void write() {
	if (!check()) ans = 0;
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}