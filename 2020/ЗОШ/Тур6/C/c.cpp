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
	edge(int a, int b) {
		to = a, cost = b;
	}
};

const int INF = 1e9 + 10;

vector<int> djkstra(vector<vector<edge> > & g, int s) {
	int n = g.size();
	vector<int> d(n, INF);
	d[s] = 0;
	set<pair<int, int>> q;
	q.insert({0, s});
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			if (d[i.to] <= d[v] + i.cost) continue;
			q.erase({d[i.to], i.to});
			d[i.to] = d[v] + i.cost;
			q.insert({d[i.to], i.to});
		}
	}
	return d;
}  

void dfs(int v, vector<bool> & used, vector<vector<edge> > & g, vector<int> & d) {
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i.to]) continue;
		if (d[i.to] != d[v] - i.cost) continue;
		dfs(i.to, used, g, d);
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	int s, to1, to2;
	cin >> s >> to1 >> to2;
	vector<vector<edge> > g(n);
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
	auto d = djkstra(g, s);
	vector<bool> used1(n, false), used2(n, false);
	dfs(to1, used1, g, d);
	dfs(to2, used2, g, d);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (used1[i] && used2[i])
			chkmax(ans, d[i]);
	}
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}