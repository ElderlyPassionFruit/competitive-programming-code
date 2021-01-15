#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

struct node{
	int val, prior, sz;
	node *l, *r;
	node() {

	}
	node(int new_val) {
		val = new_val;
		prior = rnd();
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
};

int sz(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr)
		return;
	tree->sz = sz(tree->l) + sz(tree->r) + 1;
}

node * merge(node * tree_l, node * tree_r) {
	if (tree_l == nullptr)
		return tree_r;
	if (tree_r == nullptr)
		return tree_l;
	if (tree_l->prior < tree_r->prior) {
		tree_l->r = merge(tree_l->r, tree_r);
		upd(tree_l);
		return tree_l;
	}
	else {
		tree_r->l = merge(tree_l, tree_r->l);
		upd(tree_r);
		return tree_r;
	}
}

pair <node *, node *> split(node * tree, int val) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->val > val) {
		auto p = split(tree->l, val);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, val);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

node * insert(node * tree, node * x) {
	if (tree == nullptr)
		return x;
	if (x == nullptr)
		return tree;
	if (x->prior < tree->prior) {
		auto p = split(tree, x->val);
		x->l = p.first;
		x->r = p.second;
		upd(x);
		return x;
	}
	else {
		if (tree->val > x->val) {
			tree->l = insert(tree->l, x);
		}
		else {
			tree->r = insert(tree->r, x);
		}
		upd(tree);
		return tree;
	}
}

node * erase(node * tree, int x) {
	if (tree == nullptr)
		return nullptr;
	if (tree->val == x)
		return merge(tree->l, tree->r);
	else if (tree->val > x) {
		tree->l = erase(tree->l, x);
		upd(tree);
		return tree;
	}
	else {
		tree->r = erase(tree->r, x);
		upd(tree);
		return tree;
	}
}

int Get(node * tree, int y1, int y2) {
	int ans1 = 0;
	int ans2 = 0;
	auto u = split(tree, (y1 + y2 - 1) / 2);
	
	ans1 = sz(u.first);
	tree = merge(u.first, u.second);
	
	u = split(tree, (y1 + y2) / 2);
	ans2 = sz(u.second);

	tree = merge(u.first, u.second);
	return ans1 - ans2;
}

struct segment_tree{
	vector<node*> tree;
	vector<int> pos;
	int n;
	segment_tree() {
		n = 0;
		tree = {};
		pos = {};
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = new node(a[tl]);
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = nullptr;
		for (int i = tl; i < tr; i++)
			tree[v] = insert(tree[v], new node(a[i]));
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.resize(4 * n);
		pos.resize(n);
		build(1, 0, n, a);
	}

	int get(int v, int tl, int tr, int l, int r, int y1, int y2) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return Get(tree[v], y1, y2);
		int tm = (tl + tr) / 2;
		return get(v * 2, tl, tm, l, r, y1, y2) + get(v * 2 + 1, tm, tr, l, r, y1, y2);
	}

	int get(int l, int r, int y1, int y2) {
		return get(1, 0, n, l, r + 1, y1, y2);
	}

	void Insert(int p, int val) {
		int v = pos[p];
		while (v) {
			tree[v] = insert(tree[v], new node(val));
			v /= 2;
		}
	}

	void Erase(int p, int val) {
		int v = pos[p];
		while (v) {
			tree[v] = erase(tree[v], val);
			v /= 2;
		}
	}
};

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

segment_tree tree;

void build() {
	tree = segment_tree(a);
}

int sq(int x1, int y1, int x2, int y2) {
	return (x2 - x1 + 1) * (y2 - y1);
}

int get(int x1, int y1, int x2, int y2) {
	int ans = tree.get(x1, x2, y1, y2);
	if (ans == 0) return 0;
	else if (ans > 0) return 1;
	else return 2;
}

void upd(int pos, int val) {
	tree.Erase(pos, a[pos]);
	a[pos] = val;
	tree.Insert(pos, a[pos]);
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			x1--;
			x2--;
			int fans = get(x1, y1, x2, y2);
			ans.push_back(fans);
		}
		else if (type == 'C') {
			int pos, val;
			cin >> pos >> val;
			pos--;
			upd(pos, val);
		}
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