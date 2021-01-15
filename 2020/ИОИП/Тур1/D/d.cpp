#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;
int p[MAXN];
vector<int> g[MAXN];
bool used[MAXN];
int n, k;

void read() {
	cin >> n >> k;
	p[0] = -1;
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
		g[p[i]].push_back(i);
	}
}

int l[MAXN], r[MAXN], tin[MAXN], rtin[MAXN], h[MAXN], timer = 0;

struct node{
	int val, pos, mod;
	node() {
		pos = -1, mod = 0;
	}
	node(int _val, int _pos) {
		val = _val, pos = _pos, mod = 0;
	}
};

node merge(const node & a, const node & b) {
	if (a.pos == -1) return b;
	if (b.pos == -1) return a;
	if (a.val >= b.val) return a;
	return b;
}

struct segment_tree{
	vector<node> tree;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr, const vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = node(a[tl], tl);
			return; 
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(const vector<int> & a) {
		n = a.size();
		tree.resize(4 * n);
		build(1, 0, n, a);
	}

	node get_val(int v) {
		return node(tree[v].val + tree[v].mod, tree[v].pos);
	}

	void push(int v) {
		tree[v].val += tree[v].mod;
		tree[v * 2].mod += tree[v].mod;
		tree[v * 2 + 1].mod += tree[v].mod;
		tree[v].mod = 0;
	}

	void upd(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			tree[v].mod--;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r);
		upd(v * 2 + 1, tm, tr, l, r);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int l, int r) {
		upd(1, 0, n, l, r + 1);
	}

	node get() {
		return get_val(1);
	}
};

segment_tree tree;

void del(int v) {
	while (v != -1) {
		for (auto i : g[v]) {
			p[i] = -1;
		}
		tree.upd(l[v], r[v]);
		used[v] = true;
		v = p[v];
	}
}

void dfs(int v, int len) {
	tin[v] = timer++;
	rtin[tin[v]] = v;
	l[v] = tin[v];
	r[v] = tin[v];
	h[v] = ++len;
	for (auto i : g[v]) {
		dfs(i, len);
		chkmin(l[v], l[i]);
		chkmax(r[v], r[i]);
	}
}


void build() {
	dfs(0, 0);
	vector<int> have(n);
	for (int i = 0; i < n; i++)
		have[tin[i]] = h[i];
	tree = segment_tree(have);
}

int ans;

void run() {
	ans = 0;
	build();
	for (int i = 0; i < k; i++) {
		node have = tree.get();
		if (have.val <= 0) break;
		ans += have.val;
		del(rtin[have.pos]);
	}
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