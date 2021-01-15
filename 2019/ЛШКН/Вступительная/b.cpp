#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m, s, f;
const int MAXN = 1e5 + 10;
vector <pair<int, int> > g[MAXN], gr[MAXN];

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.second > b.second;
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		a--;
		b--;
		g[a].push_back({b, cost});
	}
	for (int i = 0; i < n; i++) {
		sort(g[i].begin(), g[i].end(), cmp);
		for (int j = 0; j < g[i].size(); j++) {
			gr[i].push_back({g[i][j].first, j});
		}
	}
	cin >> s >> f;
	s--;
	f--;
}

int ans = -1;
const int INF = 1e9 + 10;
void run() {
/*	cout << "gr = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << " j = " << endl;
		for (auto j : gr[i])
			cout << j.first << " " << j.second << " next = ";
		cout << endl;
	}*/
	vector <int> dist(n + 10, INF);
	dist[s] = 0;
	set <pair <int, int> > q;
	q.insert({0, s});
	while (!q.empty()) {
		auto x = *q.begin();
		q.erase(q.begin());
		int v = x.second;
		int d = x.first;
		for (auto i : gr[v]) {
			if (dist[i.first] > max(i.second, d)) {
				q.erase({dist[i.first], i.first});
				dist[i.first] = max(i.second, d);
				q.insert({dist[i.first], i.first});
			}
		}
	}
	if (dist[f] != INF)
		ans = max(0LL, dist[f] - 1);
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