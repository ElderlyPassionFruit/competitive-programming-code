#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define data data228
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to;
	ll cost;
	edge() {}
	edge(int _to, ll _cost) {
		to = _to, cost = _cost;
	}
};

struct event{
	int u, v;
	ll cost;
	event() {}
	event(int _u, int _v, ll _cost) {
		u = _u, v = _v, cost = _cost;
	}
};

const int MAXN = 1e5 + 10;
vector<edge> g[MAXN];
vector<event> ed;

int n, q;
ll w;

void read() {
	cin >> n >> q >> w;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		ll c;
		cin >> u >> v >> c;
		u--;
		v--;
		ed.push_back({u, v, c});
		g[u].push_back({v, c});
		g[v].push_back({u, c});
	}
}

bool used[MAXN];
int sz[MAXN];
int centr;

void dfs_centroid(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		if (used[to]) continue;
		dfs_centroid(to, v, size);
		chkmax(mx, sz[to]);
		sz[v] += sz[to];
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

const int MAXLOG = 17;

int tin[MAXLOG][MAXN];
int tout[MAXLOG][MAXN];
int ind[MAXLOG][MAXN];
int timer;
vector<vector<ll>> dist[MAXN];

void dfs_calc(int v, int p, int centr, int Ind, int H, ll len) {
	tin[H][v] = timer++;
	ind[H][v] = Ind;
	dist[centr][dist[v].size() - 1].push_back(len);
	
	for (auto [to, cost] : g[v]) {
		if (used[to]) continue;
		if (to == p) continue;
		dfs_calc(to, v, centr, Ind, H, len + cost);
	}

	tout[H][v] = timer;
}

int par[MAXN];
int h[MAXN];

void find_centroid(int v, int p, int H, int size) {
	dfs_centroid(v, -1, size);
	v = centr;
	par[v] = p;
	used[v] = true;
	h[v] = H;
	int Ind = 0;
	for (auto [to, cost] : g[v]) {
		if (used[to]) continue;
		dfs_calc(to, -1, v, Ind++, H, cost);
	}

	for (auto [to, cost] : g[v]) {
		if (used[to]) continue;
		int fsz = sz[to];
		if (fsz > sz[v]) fsz = size - sz[v];
		find_centroid(to, v, H + 1, size);
	}
}

struct segment_tree{
	vector<ll> tree;
	int n;
	segment_tree() {}

	segment_tree(vector<ll> a) {
		n = a.size();
		tree = a;
	}

	void upd(int l, int r, ll add) {
		for (int i = l; i <= r; i++) {
			tree[i] += add;
		}
	}

	ll get() {
		ll ans = 0;
		for (auto i : tree)
			chkmax(ans, i);
		return ans;
	}
};

struct fsetik{
	int v;
	ll dist;
	fsetik() {}
	fsetik(int _v, ll _dist) {
		v = _v, dist = _dist;
	}
};

bool operator<(const fsetik & a, const fsetik & b) {
	return tie(a.dist, a.v) < tie(b.dist, b.v);
}

vector<segment_tree> data[MAXN];
set<fsetik> help[MAXN];
set<fsetik> fans;

void build() {
	find_centroid(0, -1, 0, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < dist[i].size(); j++) {
			data[i].push_back(segment_tree(dist[i][j]));
			help[i].insert({j, data[i][j].get()});
		}
		if (help[i].size() == 1) {
			fans.insert({i, help[i].begin()->dist});
		} 
		else if (help[i].size() >= 2) {
			ll have = 0;
			auto it = help[i].end();
			--it;
			have += it->dist;
			--it;
			have += it->dist;
			fans.insert({i, have});
		}
	}
}

void upd(int ind, ll c) {
	int v = ed[ind].v;
	int u = ed[ind].u;
	ll add = c - ed[ind].cost;
	ed[ind].cost = c;
	
	while (now != -1) {

	}	
}

ll get() {
	assert(fans.size());
	return (--fans.end())->dist;
}

vector<ll> ans;

void run() {
	build();
	ll last = 0;
	while (q--) {
		int ind;
		ll c;
		cin >> ind >> c;
		ind = (ll) (ind + last) % (n - 1);
		c = (c + last) % w;
		upd(ind, c);
		last = get();
		ans.push_back(last);
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