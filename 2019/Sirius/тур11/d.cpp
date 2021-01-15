#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
const int MAXN = 1e5 + 10;
vector <pair <int, int> > g[MAXN];
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int s;
		cin >> s;
		vector <int> ve;
		vector <int> ti;
		ti.push_back(0);
		for (int j = 0; j < 2*s + 1; j++) {
			int x;
			cin >> x;
			if (j % 2 == 0) {
				x--;
				ve.push_back(x);
			} 
			else {
				ti.push_back(x);
			}
		}
		for (int x = 1; x < ti.size(); x++) {
			ti[x] = ti[x] + ti[x - 1];
		}

		for (int v = 0; v < ve.size(); v++) {
			for (int u = v + 1; u < ve.size(); u++) {
				int cost = ti[u] - ti[v];
				g[ve[v]].push_back({ve[u], cost}); 
			}
		}
	}
}
const int INF = 1e18;
pair <int, int> ans;

void run() {
/*	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		for (auto u : g[i]) {
			cout << "v = " << i << " u = " << u.first << " cost = " << u.second << endl; 
		}
	}*/

	vector <pair <int, int> > dist(n, {INF, -INF});
	set <pair <pair <int, int>, int> > q;
	dist[0] = {0, 0};
	q.insert({dist[0], 0});
	while (!q.empty()) {
		auto p = *q.begin();
		q.erase(q.begin());
		int v = p.second;
		int d = p.first.first;
		int d_d = p.first.second;
		for (auto u : g[v]) {
			if (dist[u.first].first > d + u.second || (dist[u.first].first == d + u.second && dist[u.first].second < d_d + u.second*u.second)) {
				q.erase({dist[u.first], u.first});
				dist[u.first].first = d + u.second;
				dist[u.first].second = d_d + u.second*u.second;
				q.insert({dist[u.first], u.first});
			}
		}
	}
	ans = dist[n - 1];
}

void write() {
	cout << ans.first << " " << ans.second << endl;
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