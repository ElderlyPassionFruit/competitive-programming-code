#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

const int MAXN = 1e5 + 10;

struct ed{
	int v, cost;
	ed() {}
	ed(int a, int b) {
		v = a, cost = b;
	}
};

vector<ed> g[MAXN];
int n, m;
int color[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> color[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back({v, color[u] != color[v]});
		g[v].push_back({u, color[u] != color[v]});
	}
}

int ans;
vector<int> path;
const int INF = 1e9;
int dist[MAXN];
int p[MAXN];

void run() {
	for (int i = 0; i < n; i++)
		dist[i] = INF;
	dist[0] = 0;
	p[0] = 0;
	set<pair<int, int> > q;
	q.insert({0, 0});
	while (!q.empty()) {
		auto v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			if (dist[i.v] > dist[v] + i.cost) {
				q.erase({dist[i.v], i.v});
				dist[i.v] = dist[v] + i.cost;
				p[i.v] = v;
				q.insert({dist[i.v], i.v});
			}
		}
	}
	if (dist[n - 1] == INF) {
		cout << "impossible" << endl;
		exit(0);
	}
	int f = n - 1;
	ans = dist[n - 1];
	while (f != 0) {
		path.push_back(f);
		f = p[f];
	}
	path.push_back(0);
	reverse(all(path));
}

void write() {
	cout << ans << " " << path.size() << endl;
	for (auto i : path)
		cout << i + 1 << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}









