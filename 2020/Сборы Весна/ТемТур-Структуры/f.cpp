#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 228 + 1337;

struct node{
	int min_val, second_min_val, cnt_min_val;
	ll sum;
	int mod;
	int sz;
	node() {
		sz = 0;
		mod = -1;
		min_val = -1;
		second_min_val = INF;
		cnt_min_val = 0;
		sum = 0;
	}
	node(int x) {
		min_val = x;
		second_min_val = INF;
		cnt_min_val = 1;
		sum = x;
		mod = -1;
		sz = 1;
	}
	void wr() {

	}
};

node merge(const node & a, const node & b) {
	if (!a.sz) return b;
	if (!b.sz) return a;
	node ans;
	ans.mod = -1;
	ans.sum = a.sum + b.sum;
	ans.sz = a.sz + b.sz;
	ans.min_val = min(a.min_val, b.min_val);
	if (a.min_val == ans.min_val) ans.cnt_min_val += a.cnt_min_val;
	if (b.min_val == ans.min_val) ans.cnt_min_val += b.cnt_min_val;
	if (a.min_val == b.min_val) {
		ans.second_min_val = min(a.second_min_val, b.second_min_val);
	} else if (a.min_val < b.min_val) {
		ans.second_min_val = min(a.second_min_val, b.min_val);
	} else if (a.min_val > b.min_val) {
		ans.second_min_val = min(a.min_val, b.second_min_val);
	}
	return ans;
}

struct segment_tree{
	vector<node> tree;
	int n;

	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			tree[v] = node(0);
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(n * 4, {});
		build(1, 0, n);
	}

	void push(int v, int tl, int tr) {
		if (tree[v].mod == -1) return;
		if (tl != tr - 1) {
			chkmax(tree[v * 2].mod, tree[v].mod);
			chkmax(tree[v * 2 + 1].mod, tree[v].mod);
		}
		if (tree[v].min_val >= tree[v].mod) return;
		assert(tree[v].mod < tree[v].second_min_val);
		tree[v].sum += (ll)(tree[v].mod - tree[v].min_val) * tree[v].cnt_min_val;
		tree[v].min_val = tree[v].mod;
		tree[v].mod = -1;
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		push(v, tl, tr);
		if (tl >= r || tr <= l || tree[v].min_val >= val) return;
		if (tl >= l && tr <= r && tree[v].second_min_val > val) {	
			tree[v].mod = val;
			push(v, tl, tr);
			return;
		}
		if (tl == tr - 1) return;
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
	}

	ll get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		push(v, tl, tr);
		if (tl >= l && tr <= r) {
			return tree[v].sum;
		}
		int tm = (tl + tr) / 2;
		ll ans = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
		return ans;
	}

	ll get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

ll gcd(ll a, ll b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	while (cin >> n >> k ) {
		if (n == 0 && k == 0) return 0;
		segment_tree tree(n);
		while (k--) {
			char type;
			cin >> type;
			if (type == '?') {
				int l, r;
				cin >> l >> r;
				l--;
				r--;
				ll fans = tree.get(l, r);
				int len = r - l + 1;
				int g = gcd(fans, len);
				fans /= g;
				len /= g;
				if (len == 1) {
					cout << fans << "\n";
				} else {
					cout << fans << "/" << len << "\n";
				}
			} else {
				int l, r, val;
				cin >> l >> r >> val;
				l--;
				r--;
				tree.upd(l, r, val);
			}
		}
	}
	return 0;
}