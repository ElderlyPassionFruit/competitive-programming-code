#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

struct node{
	int prior, val, sz;
	node *l, *r;
	node(int new_val) {
		prior = rnd();
		val = new_val;
		sz = 1;
		l = r = nullptr;
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
	tree->sz = 1 + sz(tree->l) + sz(tree->r);
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

pair <node *, node *> split_size(node * tree, int size) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= size) {
		auto p = split_size(tree->l, size);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	} 
	else {
		auto p = split_size(tree->r, size - sz(tree->l) - 1);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

pair <node *, node *> split_val(node * tree, int val) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->val >= val) {
		auto p = split_val(tree->l, val);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	} 
	else {
		auto p = split_val(tree->r, val);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

node * insert(node * tree, node * v) {
	if (tree == nullptr)
		return v;
	if (v == nullptr)
		return tree;
	if (v->prior < tree->prior) {
		auto p = split_val(tree, v->val);
		v->l = p.first;
		v->r = p.second;
		upd(v);
		return v;
	}
	else {
		if (tree->val >= v->val)
			tree->l = insert(tree->l, v);
		else
			tree->r = insert(tree->r, v);
		upd(tree);
		return tree;
	}
}

node * erase(node * tree, int v) {
	if (tree == nullptr)
		return nullptr;
	if (tree->val == v)
		return merge(tree->l, tree->r);
	if (tree->val > v)
		tree->l = erase(tree->l, v);
	else 
		tree->r = erase(tree->r, v);
	upd(tree);
	return tree;
}

struct event{
	int type, val, ind;
	event() {}
	event(int a, int b, int v) {
		val = a, type = b, ind = v;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.val, a.type, a.ind) < tie(b.val, b.type, b.ind);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<event> a;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		r++;
		a.push_back({l, 1, i});
		a.push_back({r, 2, i});
	}
	sort(a.begin(), a.end());
	node * tree = nullptr;
	int pos = 0;
	for (int i = 1; i <= n; i++) {
		while (pos < a.size() && a[pos].val == i) {
			if (a[pos].type == 1) {
				tree = insert(tree, new node(a[pos].ind));
			}
			else {
				tree = erase(tree, a[pos].ind);
			}
			pos++;
		}
		auto p = split_size(tree, i);
		auto v = split_size(p.first, i - 1);
		if (v.second == nullptr) {
			cout << -1 << " ";
		}
		else {
			cout << v.second->val + 1 << " ";
		}
		p.first = merge(v.first, v.second);
		tree = merge(p.first, p.second);
	}
	cout << endl;
	return 0;
}










