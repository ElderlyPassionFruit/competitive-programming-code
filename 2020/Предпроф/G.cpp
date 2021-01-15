#include <bits/stdc++.h>

using namespace std;
#define all(a) a.begin(), a.end()

int n, m, s, f;
const int INF = 1e9 + 228 + 1337;
const int MAXN = 2e4 + 10;
vector<pair<int, int>> g[MAXN];

signed main() {
	cin >> n >> m >> s >> f;
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
	vector<int> dist(n, INF);
	vector<int> p(n, -1);
	dist[s] = 0;
	set<pair<int, int>> q;
	q.insert({0, s});
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			int u = i.first;
			int cost = i.second;
			if (dist[u] <= dist[v] + cost) continue;
			q.erase({dist[u], u});
			dist[u] = dist[v] + cost;
			p[u] = v;
			q.insert({dist[u], u});
		}
	}
	assert(dist[f] != INF);
	vector<int> ans;
	ans.push_back(f);
	while (f != s) {
		ans.push_back(p[f]);
		f = p[f];
	}
	reverse(all(ans));
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}