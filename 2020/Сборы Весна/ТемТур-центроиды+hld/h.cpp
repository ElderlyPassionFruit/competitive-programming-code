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

const int MAXN = 5e5 + 10, MAXLOG = 20;
int n, q;
vector<edge> g[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int p, cost;
		cin >> p >> cost;
		p--;
		g[i].push_back({p, cost});
		g[p].push_back({i, cost});
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

struct fhave{
	int dist, ind;
	fhave() {}
	fhave(int _dist, int _ind) {
		dist = _dist, ind = _ind;
	}
};

bool operator<(const fhave & a, const fhave & b) {
	return a.ind < b.ind;
}

vector<fhave> have[MAXN];

void color(int v) {
	int now = v;
	int H = h[v];
	while (now != -1) {
		have[now].push_back({dist[v][H], v});
		H--;
		now = par[now];
	}
}

const int INF = 1e18;

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr, const vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(const vector<int> & a) {
		n = a.size();
		if (n == 0) return;
		tree.assign(4 * n, INF);
		build(1, 0, n, a);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return INF;
		if (tl >= l && tr <= r) return tree[v];
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		if (l > r) return INF;
		if (n == 0) return INF;
		return get(1, 0, n, l, r + 1);
		int ans = INF;
		for (int i = l; i <= r; i++)
			chkmin(ans, tree[i]);
		return ans;
	}
};

segment_tree tree[MAXN];

void build() {
	dfs_centroid(0, -1, n, -1, 0);
	build(centr, -1, n, 0);
	for (int i = 1; i < n; i++) {
		if ((int)g[i].size() != 1) continue;
		color(i);
	}
	for (int i = 0; i < n; i++) {
		sort(all(have[i]));
		vector<int> a;
		for (auto [dist, ind] : have[i]) {
			a.push_back(dist);
		}
		tree[i] = segment_tree(a);
	}
}

int get(int v, int l, int r) {
	int now = v;
	int H = h[v];
	int ans = INF;
	while (now != -1) {
		int L = lower_bound(all(have[now]), fhave(0, l)) - have[now].begin();
		int R = --upper_bound(all(have[now]), fhave(0, r)) - have[now].begin();
		chkmin(ans, dist[v][H] + tree[now].get(L, R));
		H--;
		now = par[now];
	}
	return ans;
}

void run() {
	build();
	while (q--) {
		int v, l, r;
		cin >> v >> l >> r;
		v--;
		l--;
		r--;
		cout << get(v, l, r) << "\n";
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