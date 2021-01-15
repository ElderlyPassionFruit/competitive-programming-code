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
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};
 
const int MAXN = 1e5 + 10;
vector<edge> g[MAXN];
int n, m;
int s1, t1;
int s2, t2;
 
void read() {
	cin >> n >> m;
	cin >> s1 >> t1;
	s1--;
	t1--;
	cin >> s2 >> t2;
	s2--;
	t2--;
	for (int i = 0; i < m; i++) {
		int u, v;
		int c;
		cin >> u >> v >> c;
		u--;
		v--;
		g[u].push_back({v, c});
		g[v].push_back({u, c});
	}
}
 
const ll INF = 1e18;
ll ans;
 
vector<ll> djkstra(int v) {
	vector<ll> d(n, INF);
	set<pair<ll, int>> q;
	d[v] = 0;
	q.insert({0, v});
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto [to, cost] : g[v]) {
			if (d[to] <= d[v] + cost) continue;
			q.erase({d[to], to});
			d[to] = d[v] + cost;
			q.insert({d[to], to});
		}
	}
	return d;
}
 
vector<ll> dist;
 
void build() {
	auto d = djkstra(s1);
	dist.assign(n, INF);
	queue<int> q;
	q.push(t1);
	dist[t1] = d[t1];
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto [to, cost] : g[v]) {
			if (dist[to] != INF) continue;
			if (d[to] + cost != d[v]) continue;
			dist[to] = d[to];
			q.push(to);
		}
	}
}
 
vector<ll> dp1;
vector<bool> used;
 
ll dfs1(int v) {
	if (used[v]) return dp1[v];
	used[v] = true;
	for (auto [to, cost] : g[v]) {
		if (dist[v] + cost != dist[to]) continue;
		chkmin(dp1[v], dfs1(to));
	}
	return dp1[v];
}
 
vector<ll> dp2;

ll dfs2(int v) {
	if (used[v]) return dp2[v];
	used[v] = true;
	for (auto [to, cost] : g[v]) {
		if (dist[v] != dist[to] + cost) continue;
		chkmin(dp2[v], dfs2(to));
	}
	return dp2[v];
}
 
void run() {
	build();
	dp1 = dp2 = djkstra(t2);
	used.assign(n, false);
	dfs1(s1);
	used.assign(n, false);
	dfs2(t1);

	vector<ll> have = djkstra(s2);
	ans = have[t2];
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF) continue;
		chkmin(ans, min(dp1[i], dp2[i]) + have[i]);
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