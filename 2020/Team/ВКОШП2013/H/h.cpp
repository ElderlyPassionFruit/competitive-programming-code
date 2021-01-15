#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
const int MAXN = 5e3 + 10;
const int INF = 1e18;
struct ed{
	int v, cost;
	ed() {}
	ed(int a, int b) {
		v = a, cost = b;
	}
};

vector<ed> g[MAXN];
int color[MAXN];
int d[MAXN], p[MAXN];
int n, m;

struct event{
	int d, v, p;
	event() {}
	event(int a, int b, int c) {
		d = a, v = b, p = c;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.d, a.v, a.p) < tie(b.d, b.v, b.p);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("secure.in", "r", stdin);
	freopen("secure.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> color[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}

	set<event> q;

	for (int i = 0; i < n; i++) {
		d[i] = INF;
		if (color[i] == 1) {
			d[i] = 0;
			p[i] = i;
			q.insert({0, i, i});
		}
	}

	while (!q.empty()) {
		auto x = *q.begin();
		q.erase(q.begin());
		for (auto i : g[x.v]) {
			if (d[i.v] > d[x.v] + i.cost) {
				q.erase({d[i.v], i.v, p[i.v]});
				d[i.v] = d[x.v] + i.cost;
				p[i.v] = x.p;
				q.insert({d[i.v], i.v, p[i.v]});
			}	
		}
	}
	pair <int, pair<int, int> > ans = {INF, {INF, INF}};
	for (int i = 0; i < n; i++) {
		if (color[i] == 2 && d[i] < INF) {
			ans = min(ans, make_pair(d[i], make_pair(p[i], i)));
		} 
	}
	if (ans.first == INF) {
		cout << -1 << endl;
	}
	else {
		cout << ans.second.first + 1 << " " << ans.second.second + 1 << " " << ans.first << endl;
	}
	return 0;
}








