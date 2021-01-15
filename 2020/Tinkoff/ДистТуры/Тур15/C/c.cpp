#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a, d;

void read() {
	cin >> n;
	a.resize(n);
	d.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> d[i];
	}
}

const ll INF = 4e18 + 1e6 + 228;

struct line{
	ll k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll _k, ll _b) {
		k = _k;
		b = _b;
	}
};

bool operator<(const line & a, const line & b) {
	return tie(a.k, a.b) > tie(b.k, b.b);
}

ll eval(line l, ll x) {
	return l.k * x + l.b;
}

struct node{
	node *l, *r;
	line x;
	node () {
		l = nullptr;
		r = nullptr;
	}
	node (line _x) {
		x = _x;
		l = nullptr;
		r = nullptr;
	}
};

struct cht{
	vector<line> l;
	node * root;
	cht() {}

	node * add(line x, node * tree, int tl = 0, int tr = 1e9 + 10) {
		if (tree == nullptr) {
			tree = new node(x);
			return tree;
		}
		int tm = (tl + tr) / 2;
		bool left = eval(x, tl) < eval(tree->x, tl);
		bool mid = eval(x, tm) < eval(tree->x, tm);
		if (mid) swap(tree->x, x);
		if (tl == tr - 1) {
			return tree;
		}
		if (left != mid) {
			tree->l = add(x, tree->l, tl, tm);
		}
		else {
			tree->r = add(x, tree->r, tm, tr);
		}
		return tree;
	}

	void add(line x) {
		root = add(x, root);
		l.push_back(x);
	}

	ll get(int x, node * tree, int tl = 0, int tr = 1e9 + 10) {
		if (tl >= x + 1 || tr <= x) return INF;
		if (tree == nullptr) return INF;
		if (tl == tr - 1) return eval(tree->x, x);
		int tm = (tl + tr) / 2;
		return min(eval(tree->x, x), min(get(x, tree->l, tl, tm), get(x, tree->r, tm, tr))); 
	}

	ll get(ll x) {
		return get(x, root);
	}
};

struct segment_tree{
	vector<cht> tree;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr, const vector<int> & a, const vector<int> & d) {
		if (tl == tr - 1) {
			tree[v].add(line(d[tl], a[tl]));
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a, d);
		build(v * 2 + 1, tm, tr, a, d);
		vector<line> fadd(tree[v * 2].l.size() + tree[v * 2 + 1].l.size());
		merge(all(tree[v * 2].l), all(tree[v * 2 + 1].l), fadd.begin());
		for (auto i : fadd)
			tree[v].add(i);
	}

	segment_tree(const vector<int> & a, const vector<int> & d) {
		n = a.size();
		tree.resize(4 * n);
		build(1, 0, n, a, d);
		return;
		for (int i = 0; i < n; i++) {
			tree[i].add(line(d[i], a[i]));
		}	
	}

	ll get(int v, int tl, int tr, int l, int r, int k) {
		if (tl >= r || tr <= l) return INF;
		if (tl >= l && tr <= r) return tree[v].get(k);
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, l, r, k), get(v * 2 + 1, tm, tr, l, r, k));
	}

	ll get(int l, int r, int k) {
		return get(1, 0, n, l, r + 1, k);
	}
};

segment_tree tree;

void build() {
	tree = segment_tree(a, d);
}

ll solve(int l, int r, int k) {
	return tree.get(l, r, k);
}

vector<ll> ans; 

void run() {
	build();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		ans.push_back(solve(l - 1, r - 1, k - 1));
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