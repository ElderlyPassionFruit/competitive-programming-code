#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};

const int MAXN = 1e5 + 10, MAXLOG = 17;
int n;
vector<edge> g[MAXN];
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
}

bool used[MAXN];
int sz[MAXN];
int centr;
int dist[MAXN][MAXLOG];
int h[MAXN];

void dfs_centroid(int v, int p, int size, int H, int len) {
	if (H != -1) {
		dist[v][H] = len;
	}
	sz[v] = 1;
	int mx = 0;
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		if (used[to]) continue;
		dfs_centroid(to, v, size, H, len + cost);
		sz[v] += sz[to];
		chkmax(mx, sz[to]);
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

int par[MAXN];

void build(int v, int p, int size, int H) {
	used[v] = true;
	par[v] = p;
	h[v] = H;
	for (auto [to, cost] : g[v]) {
		if (used[to]) continue;
		int fsz = sz[to];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		dfs_centroid(to, -1, fsz, H, cost);
		build(centr, v, fsz, H + 1);
	}
}

void build() {
	dfs_centroid(0, -1, n, -1, 0);
	build(centr, -1, n, 0);
}

struct fhave{
	int dist, t, color;
	fhave() {}
	fhave(int _dist, int _t, int _color) {
		dist = _dist, t = _t, color = _color;
	}
};

bool operator<(const fhave & a, const fhave & b) {
	return a.dist < b.dist;
}

vector<fhave> have[MAXN];

void color(int v, int c, int len, int t) {
	int now = v;
	int H = h[v];
	while (now != -1) {
		int d = len - dist[v][H];
		if (d >= 0) {
			while (!have[now].empty() && have[now].back().dist <= d) {
				have[now].pop_back();
			}
			have[now].push_back({d, t, c});
		}
		H--;
		now = par[now];
	}
}

int get(int v) {
	int now = v;
	int H = h[v];
	int ans = 0;
	int t_ans = -1;
	while (now != -1) {
		auto pos = lower_bound(have[now].rbegin(), have[now].rend(), fhave(dist[v][H], 0, 0));
		if (pos != have[now].rend() && pos->t > t_ans) {
			ans = pos->color;
			t_ans = pos->t;
		}
		H--;
		now = par[now];
	}
	return ans;
}

void run() {
	build();
	
	int q;
	cin >> q;
	int t = 0;
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int v, d, c;
			cin >> v >> d >> c;
			v--;
			color(v, c, d, t);
		} else {
			int v;
			cin >> v;
			v--;
			cout << get(v) << "\n";
		}
		t++;
	}
}

void write() {
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