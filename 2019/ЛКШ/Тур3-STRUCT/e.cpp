#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int val;
	node *l, *r;
	node() {
		val = 0;
		l = nullptr;
		r = nullptr;
	}
	node(int new_val) {
		val = new_val;
		l = nullptr;
		r = nullptr;
	} 
};

node * build(int l, int r) {
	if (l == r - 1) {
		node * tree = new node();
		return tree;
	}
	int m = (l + r) / 2;
	node * tree = new node();
	tree->l = build(l, m);
	tree->r = build(m, r);
	return tree;
}

node * clone(node * tree) {
	node * ans = new node();
	ans->val = tree->val;
	ans->l = tree->l;
	ans->r = tree->r;
	return ans;
}

node * upd(node * tree, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) {
		return tree;
	}
	if (tl >= l && tr <= r) {
		tree = clone(tree);
		tree->val = val;
		return tree;
	}
	int tm = (tl + tr) / 2;
	tree = clone(tree);
	tree->l = upd(tree->l, tl, tm, l, r, val);
	tree->r = upd(tree->r, tm, tr, l, r, val);
	tree->val = tree->l->val + tree->r->val;
	return tree;
}

int get(node * tree, int tl, int tr, int sum) {
	if (tree->val < sum) return -1;
	if (tl == tr - 1) return tl;
	int tm = (tl + tr) / 2;
	if (tree->l->val >= sum) 
		return get(tree->l, tl, tm, sum);
	else
		return get(tree->r, tm, tr, sum - tree->l->val); 
}

int n, m;
vector<int> a;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

vector<int> ans;

void run() {
	map <int, int> pos;
	for (auto i : a) pos[i] = -1;
	vector<node *> roots;
	roots.push_back(build(0, n));
	for (int i = n - 1; i >= 0; i--) {
		if (pos[a[i]] == -1) {
			node * tree = upd(roots.back(), 0, n, i, i + 1, 1);
			roots.push_back(tree);
		}
		else {
			node * tree = upd(roots.back(), 0, n, pos[a[i]], pos[a[i]] + 1, 0);
			tree = upd(tree, 0, n, i, i + 1, 1);
			roots.push_back(tree);
		}
		pos[a[i]] = i;
	}

	reverse(roots.begin(), roots.end());

	int q;
	cin >> q;
	int p = 0;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		int l = (x + p) % n;
		int k = (y + p) % m + 1;
		int fans = get(roots[l], 0, n, k);
		fans++;
		ans.push_back(fans);
		p = fans;
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