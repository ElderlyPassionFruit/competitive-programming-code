#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;

int n, m, q;
vector<int> g[MAXN];

vector<pair<int, int> > edge;

void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		edge.push_back({u, v});
	}
}

const int INF = 1e9;
int d[MAXN];
queue<int> Q;
vector<bool> good;

void build() {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[0] = 0;
	Q.push(0);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (auto i : g[v]) {
			if (d[i] != INF) continue;
			d[i] = d[v] + 1;
			Q.push(i);
		}
	}
}

set<pair<int, int> > used;

void add_edge(int u, int v) {
	if (u > v) swap(u, v);
	used.insert({u, v});
}

bool check(int u, int v) {
	if (u > v) swap(u, v);
	return used.count({u, v});
} 

int dist[MAXN];

int calc() {
	for (int i = 0; i < n; i++)
		dist[i] = INF;
	dist[0] = 0;
	set<pair<int, int> > q;
	q.insert({0, 0});
	while(!q.empty()) {
		auto v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			if (dist[i] <= dist[v] + 1) continue;
			if (check(i, v)) continue;
			q.erase({dist[i], i});
			dist[i] = dist[v] + 1;
			q.insert({dist[i], i});
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += dist[i] != d[i];
	return ans;
}

vector<int> ans;

void run() {
	build();
	for (int i = 0; i < q; i++) {
		int ind;
		cin >> ind;
		ind--;
		add_edge(edge[ind].first, edge[ind].second);
		ans.push_back(calc());
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
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