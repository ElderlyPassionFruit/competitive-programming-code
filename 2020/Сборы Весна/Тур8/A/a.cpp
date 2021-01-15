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
 
const int MAXN = 4e5 + 228;
vector<edge> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
}

const ll INF = 1e18 + 228 + 1337;

vector<ll> djkstra(int s) {
	vector<ll> d(n, INF);
	set<pair<ll, int>> q;
	d[s] = 0;
	q.insert({d[s], s});
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

ll ans;

void run() {
	vector<ll> d1 = djkstra(0);
	vector<ll> d2 = djkstra(n - 1);
	ans = d1[n - 1];
	for (int i = 0; i < n; i++) {
		ll min1 = d1[i], min2 = d2[i];
		for (auto [to, cost] : g[i]) {
			chkmin(min1, d1[to]);
			chkmin(min2, d2[to]);
		}
		chkmin(ans, min1 + min2);
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