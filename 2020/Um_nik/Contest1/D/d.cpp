#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 10;
vector<int> g[MAXN], gr[MAXN];
int n, m;
int s, f;

const int INF = 1e9 + 10;
int dist[MAXN];
bool used[MAXN];
int deg[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		v--;
		u--;
		g[v].push_back(u);
		deg[u]++;
		gr[u].push_back(v);
	}
	cin >> s >> f;
	s--;
	f--;
	fill(dist, dist + n, INF);
	dist[f] = 0;

	fill(used, used + n, false);
	used[f] = true;

	set<pair<int, int>> q;
	q.insert({0, f});

	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		if (!used[v]) {
			bool ok = true;
			for (auto i : gr[v]) {
				ok &= used[i];
			}
			if (ok) {
				used[v] = true;
				int mx = 0;
				for (auto i : gr[v]) {
					mx = max(mx, dist[i]);
				}
				dist[v] = min(dist[v], mx);
			}
		} 
		for (auto i : g[v]) {
			if (dist[i] <= dist[v] + 1) continue;
			q.erase({dist[i], i});
			dist[i] = dist[v] + 1;
			q.insert({dist[i], i});
		}
		used[v] = true;
	}

	if (dist[s] == INF) {
		cout << -1 << endl;
	} else {
		cout << dist[s] << endl;
	}
	return 0;
}