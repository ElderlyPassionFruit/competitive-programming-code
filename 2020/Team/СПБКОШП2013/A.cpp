#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int long long
const int INF = 1e16;

struct node{
	bool flag;
	int l, cnt_l, r, cnt_r;
	int mod;
	int ans;
	node() {
		l = r = 0;
		cnt_l = cnt_r = 0;
		flag = false;
		mod = 0;
		ans = 0;
	}
	node(int x) {
		flag = true;
		l = x;
		cnt_l = 1;
		r = x;
		cnt_r = 1;
		mod = 0;
		ans = 1;
	}
};
 
struct segment_tree{
	vector<node> tree;
	int n;
	segment_tree() {}

	node merge(node a, node b) {
		if (a.ans == 0) return b;
		if (b.ans == 0) return a;
		node ans;
		ans.l = a.l;
		ans.r = b.r;
		ans.cnt_l = a.cnt_l;
		ans.cnt_r = b.cnt_r;
		ans.mod = 0;
		ans.flag = false;
		ans.ans = max(a.ans, b.ans);
		if (a.flag && b.flag) {
			if (a.r == b.l - 1) {
				ans.cnt_l = ans.cnt_r = a.cnt_l + b.cnt_r;
				ans.flag = true;
				ans.ans = max(ans.ans, ans.cnt_l);
			}
		}
		else if (a.flag && !b.flag) {
			if (a.r == b.l - 1) {
				ans.cnt_l = a.cnt_l + b.cnt_l;
				ans.ans = max(ans.ans, ans.cnt_l);
			}
		}
		else if (!a.flag && b.flag) {
			if (a.r == b.l - 1) {
				ans.cnt_r = a.cnt_r + b.cnt_r;
				ans.ans = max(ans.ans, ans.cnt_r);
			}
		}
		else {
			if (a.r == b.l - 1) {
				ans.ans = max(ans.ans, a.cnt_r + b.cnt_l);
			}
		}
		return	ans;
    }

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = node(a[tl]);
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	} 
	
	segment_tree(vector<int> & a) {
		n = a.size();
		tree.resize(4 * n);
		build(1, 0, n, a);
	}

	node get_val(int v) {
		node x = tree[v];
		x.l += x.mod;
		x.r += x.mod;
		x.mod = 0;
		return x;
	}

	void push(int v) {
		tree[v * 2].mod += tree[v].mod;
		tree[v * 2 + 1].mod += tree[v].mod;
		tree[v].l += tree[v].mod;
		tree[v].r += tree[v].mod;
		tree[v].mod = 0; 
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return node();
		if (tl >= l && tr <= r) return get_val(v);
		int tm = (tl + tr) / 2;
		push(v);
		return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1).ans;
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			tree[v].mod += val;
			return;
		}
		int tm = (tl + tr) / 2;
		push(v);
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
	}
};

segment_tree tree;

void build(vector<int> & a) {
	tree = segment_tree(a);
}

void upd(int l, int r, int d) {
	tree.upd(l, r, d);
}

int get(int l, int r) {
	return tree.get(l, r);
}
 
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	build(a);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		char t;
		cin >> t;
		if (t == '+') {
			int l, r, d;
			cin >> l >> r >> d;
			l--;
			r--;
			upd(l, r, d);
		}
		else if (t == '?') {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cout << get(l, r) << "\n";
		}
	}
	return 0; 
}

//сосать