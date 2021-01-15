#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e4 + 10;
int n;
vector<int> g[MAXN];
int have[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> have[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int sz[MAXN], tin[MAXN], tout[MAXN], timer = 0, nxt[MAXN];
int h[MAXN];
int par[MAXN];

void dfs_path(int v, int p) {
	par[v] = p;
	sz[v] = 1;
	tin[v] = timer++;
	nxt[v] = -1;
	for (auto to : g[v]) {
		if (to == p) continue;
		h[to] = h[v] + 1;
		dfs_path(to, v);
		sz[v] += sz[to];
		if (nxt[v] == -1 || sz[nxt[v]] < sz[to]) {
			nxt[v] = to;
		}
	}
	tout[v] = timer++;
}

int id[MAXN];
int par_path[MAXN];
int pos[MAXN];
int path_sz[MAXN];
int it = 0, cnt = 0;

void dfs_build(int v, int p) {
	id[v] = cnt;
	if (!path_sz[cnt]) {
		par_path[cnt] = v;
	}
	path_sz[cnt]++;
	pos[v] = it++;
	if (nxt[v] != -1) {
		dfs_build(nxt[v], v);
	}
	for (auto to : g[v]) {
		if (to == p) continue;
		if (to == nxt[v]) continue;
		cnt++;
		dfs_build(to, v);
	}
}

struct segment_tree{
	vector<int> tree;
	vector<int> pos;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree(int _n) {
		n = _n;
		tree.assign(4 * n, 0);
		pos.resize(n);
		build(1, 0, n);
	}

	void upd(int v, int val) {
		v = pos[v];
		tree[v] = val;
		v /= 2;
		while (v) {
			tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
		int ans = 0;
		for (int i = l; i <= r; i++) {
			chkmax(ans, tree[i]);
		}
		return ans;
	}
};

segment_tree tree;

void build() {
	dfs_path(0, 0);
	dfs_build(0, 0);
	tree = segment_tree(n);
	for (int i = 0; i < n; i++) {
		tree.upd(pos[i], have[i]);
	}
}

int get(int a, int b) {
	int ans = 0;
	while (id[a] != id[b]) {
		if (h[par_path[id[a]]] < h[par_path[id[b]]]) {
			swap(a, b);
		}
		chkmax(ans, tree.get(pos[par_path[id[a]]], pos[a]));	
		a = par[par_path[id[a]]];
	}
	if (h[a] > h[b]) {
		swap(a, b);
	}
	chkmax(ans, tree.get(pos[a], pos[b]));
	return ans;
}

void upd(int v, int val) {
	tree.upd(pos[v], val);
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	while (q--) {
		char type;
		cin >> type;
		if (type == '!') {
			int v, val;
			cin >> v >> val;
			v--;
			upd(v, val);
		} else {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			ans.push_back(get(a, b));
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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