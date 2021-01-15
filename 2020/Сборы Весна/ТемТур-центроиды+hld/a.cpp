#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 1e5 + 10;
int n, q;
vector<int> g[MAXN];	
int c[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		g[p].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}
}

int sz[MAXN], par[MAXN], h[MAXN], tin[MAXN], tout[MAXN], timer = 0;
int nxt[MAXN];

void dfs_path(int v, int p) {
	sz[v] = 1;
	par[v] = p;
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
}

int id[MAXN], par_path[MAXN], pos[MAXN], path_sz[MAXN];
int it = 0, cnt = 0;

void dfs_build(int v, int p) {
	tin[v] = timer++;
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
	tout[v] = timer - 1;
}

struct segment_tree{
	vector<int> tree, mod;
	vector<int> arr;
	int n;

	segment_tree() {}

	segment_tree(int _n) {
		n = _n;
		arr.assign(n, 0);
		tree.assign(4 * n, 0);
		mod.assign(4 * n, 0);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
	}

	int get_val(int v, int tl, int tr) {
		return tree[v] + mod[v] * (tr - tl);
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			mod[v] += val;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = get_val(v * 2, tl, tm) + get_val(v * 2 + 1, tm, tr);
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
	}

	void upd(int pos, int val) {
		upd(pos, pos, val);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) {
			return get_val(v, tl, tr);
		}
		push(v);
		int tm = (tl + tr) / 2;
		int ans = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
		tree[v] = get_val(v * 2, tl, tm) + get_val(v * 2 + 1, tm, tr);
		return ans;
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

segment_tree tree;

void build() {
	dfs_path(0, 0);
	dfs_build(0, 0);
	tree = segment_tree(n);
	for (int i = 0; i < n; i++) {
		tree.upd(pos[i], c[i]);
	}
}

void upd_path(int a, int b, int val) {
	while (id[a] != id[b]) {
		if (h[par_path[id[a]]] < h[par_path[id[b]]]) {
			swap(a, b);
		}
		tree.upd(pos[par_path[id[a]]], pos[a], val);
		a = par[par_path[id[a]]];
	}
	if (h[a] > h[b]) {
		swap(a, b);
	}
	tree.upd(pos[a], pos[b], val);

}

int get_path(int a, int b) {
	int ans = 0;
	while (id[a] != id[b]) {
		if (h[par_path[id[a]]] < h[par_path[id[b]]]) {
			swap(a, b);
		}
		ans += tree.get(pos[par_path[id[a]]], pos[a]);
		a = par[par_path[id[a]]];
	}
	if (h[a] > h[b]) {
		swap(a, b);
	}
	ans += tree.get(pos[a], pos[b]);
	return ans;
}

void upd_subtree(int v, int val) {
	tree.upd(tin[v], tout[v], val);
}

int get_subtree(int v) {
	//cout << tin[v] << " " << tout[v] << endl;
	return tree.get(tin[v], tout[v]);
}

void upd_pos(int v, int val) {
	tree.upd(pos[v], val);
}

int get_pos(int v) {
	return tree.get(pos[v], pos[v]);
}

vector<int> ans;
const int MOD = 1e9 + 7;

void run() {
	build();
	ans.push_back(get_pos(n - 1));
	while (q--) {
		int a, b;
		cin >> a >> b;
		int s = get_path(0, a) + get_subtree(a) - get_pos(a);
		//cout << get_path(0, a) << " " << get_subtree(a) << " " << get_pos(a) << endl;
		s %= MOD;
		//cout << s << endl;
		//exit(0);
		upd_path(0, b, s);
		upd_subtree(b, s);
		upd_pos(b, -s);
		ans.push_back(get_pos(n - 1));
	}
}

void write() {
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
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