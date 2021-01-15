#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};

int n, m;
vector<int> t;
vector<vector<edge>> g;

const int INF = 1e9 + 288;

void solve() {
	int a, b, k, type;
	cin >> a >> b >> k >> type;
	vector<bool> good(n, false);
	vector<int> have = t;
	sort(all(have));
	if (type) reverse(all(have));
	//cout << have[k - 1] << endl;
	for (int i = 0; i < n; i++) {
		if (type == 0 && have[k - 1] >= t[i]) {
			good[i] = true;
		} else if (type == 1 && have[k - 1] <= t[i]) {
			good[i] = true;
		}
	}
	a--;
	b--;
	good[a] = true;
	good[b] = true;
	
	/*cout << "good = " << endl;
	for (auto i : good) {
		cout << i << " ";
	}
	cout << endl;*/
	vector<int> dist(n, INF);
	dist[a] = 0;
	set<pair<int, int>> q;
	q.insert({0, a});
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto [to, cost] : g[v]) {
			if (!good[to]) continue;
			if (dist[to] <= dist[v] + cost) continue;
			q.erase({dist[to], to});
			dist[to] = dist[v] + cost;
			q.insert({dist[to], to});
		}
	}
	if (dist[b] != INF) {
		cout << dist[b] << endl;
	} else {
		cout << -1 << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	t.resize(n);
	for (auto &i : t) {
		cin >> i;
	}
	g.assign(n, {});
	for (int i = 0; i < m; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		a--;
		b--;
		g[a].push_back({b, cost});
		g[b].push_back({a, cost});
	}
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
	return 0;
}