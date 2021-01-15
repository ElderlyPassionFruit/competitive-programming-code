#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};

const int MAXN = 1e5 + 10;
int n;
vector<edge> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
}

int sz[MAXN];
ll dp[MAXN];

void dfs_down(int v, int p) {
	sz[v] = 1;
	dp[v] = 0;
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		dfs_down(to, v);
		dp[v] += dp[to] + (ll) sz[to] * cost;
		sz[v] += sz[to];
	}
}

void dfs_up(int v, int p) {
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		dp[to] += dp[v] - (ll) sz[to] * cost - dp[to] + (ll) (n - sz[to]) * cost;
		dfs_up(to, v);
	}
}

void run() {
	dfs_down(0, 0);
	dfs_up(0, 0);
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << dp[i] << " ";
	}
	cout << endl;
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