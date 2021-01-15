#include <bits/stdc++.h>

using namespace std;
#define int long long

struct ed{
	int u, l, t, ind;
	ed(){

	}
	ed(int a, int b, int c, int d) {
		u = a, l = b, t = c, ind = d;
	}
};

const int MAXN = 3e3 + 10;
int n, m;
vector<ed> g[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, l, t;
		cin >> u >> v >> l >> t;
		u--;
		v--;
		g[u].push_back({v, l, t, i});
		g[v].push_back({u, l, t, i});
	}
}

int used[MAXN];

void dfs(int v, int p, int ind) {
	used[v] = ind;
	for (auto i : g[v]) {
		if (i.u != p && i.t == 1) {
			dfs(i.u, v, i.ind);
		}
	} 
}

const int INF = 1e18 + 10;
vector<int> ans;

void run() {
	dfs(0, 0, -1);
	cout << "used =";
	for (int i = 0; i < n; i++)
		cout << used[i] << " ";
	cout << endl;

	ans.assign(n, INF);
	vector<int> d(n, INF);
	d[0] = 0;
	ans[0] = 0;
	set<pair <pair<int, int>, int> > q;
	q.insert({{0, 0}, -1});
	while (!q.empty()) {
		auto p = *q.begin();
		q.erase(q.begin());
		int v = p.first.second;
		int dist = p.first.first;
		int ind = p.second;
		for (auto i : g[v]) {
			if (d[i.u] > dist + i.l) {
				q.erase({{d[i.u], i.u}, i.ind});
				d[i.u] = dist + i.l;
				q.insert({{d[i.u], i.u}, i.ind});
			}
			if (i.ind != used[i.u] && i.ind != ind)
				ans[i.u] = min(ans[i.u], dist + i.l);
		}
	}
}

void write() {
	for (int i = 1; i < n; i++) {
		if (ans[i] != INF) cout << ans[i] << " ";
		else cout << -1 << " ";
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