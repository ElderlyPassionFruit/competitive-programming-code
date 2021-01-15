#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int max;
	ll sum;
	node() {
		sum = 0;
		max = 0;
	}
	node(int val) {
		max = val;
		sum = val;
	}
};

node merge(const node & a, const node & b) {
	node ans = node();
	ans.sum = a.sum + b.sum;
	ans.max = max(a.max, b.max);
	return ans;
}

struct segment_tree{
	vector<node> tree;
	vector<int> pos;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr, const vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = node(a[tl]);
			//cout << tree[v].sum << " " << tree[v].max << endl;
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(const vector<int> & a) {
		n = a.size();
		tree.assign(4 * n, {});
		pos.resize(n, 0);
		build(1, 0, n, a);
	}

	ll get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return tree[v].sum;
		int tm = (tl + tr) / 2;
		return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
	}

	ll get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}

	void relax(int v, int tl, int tr, int mod) {
		if (tree[v].max < mod) return;
		if (tl == tr - 1) {
			tree[v].max %= mod;
			tree[v].sum %= mod;
			return;
		}
		int tm = (tl + tr) / 2;
		relax(v * 2, tl, tm, mod);
		relax(v * 2 + 1, tm, tr, mod);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	} 

	void upd(int v, int tl, int tr, int l, int r, int mod) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			//cout << "tl = " << tl << " tr = " << tr << endl;
			relax(v, tl, tr, mod);
			return;
		}
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, mod);
		upd(v * 2 + 1, tm, tr, l, r, mod);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	void upd(int l, int r, int mod) {
		upd(1, 0, n, l, r + 1, mod);
	}

	void upd(int v, int val) {
		v = pos[v];
		tree[v] = node(val);
		v /= 2;
		while (v) {
			tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	void wr() {
		cout << "tree = " << endl;
		for (int i = 0; i < n; i++) {
			cout << get(i, i) << " ";
		}
		cout << endl;
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	segment_tree tree(a);
	//tree.wr();
	//return 0;
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cout << tree.get(l, r) << "\n";
		} else if (type == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			r--;
			tree.upd(l, r, x);
		} else {
			int pos, val;
			cin >> pos >> val;
			pos--;
			tree.upd(pos, val);
		}
		//tree.wr();
	}
	return 0;
}