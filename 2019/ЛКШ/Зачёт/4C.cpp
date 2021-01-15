#include <bits/stdc++.h>

using namespace std;
const long long INF = -1e9;
struct node{
	long long prior, val, sz, max, must;
	node *l, *r;
	node() {
	}
	node(long long new_val) {
		prior = (rand() << 16) | rand();
		l = nullptr;
		r = nullptr;
		val = new_val;
		max = val;
		sz = 1;
		must = 0;
	}
};

long long must(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->must;
}

long long val(node * tree) {
	if (tree == nullptr)
		return INF;
	return tree->val + tree->must;
}

long long max(node * tree) {
	if (tree == nullptr)
		return INF;
	return tree->max;
}

long long sz(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr)
		return;
	tree->sz = 1 + sz(tree->l) + sz(tree->r);
	tree->max = max(tree->val, max(max(tree->l), max(tree->r)));
}

void push(node * tree, long long must) {
	if (tree == nullptr)
		return;
	tree->must += must;
}

void push(node * tree) {
	if (tree == nullptr)
		return;
	push(tree->l, must(tree));
	push(tree->r, must(tree));
	tree->val += must(tree);
	tree->must = 0;
}

node * merge(node * tree_l, node * tree_r) {
	push(tree_l);
	push(tree_r);
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

pair <node *, node *> split_size(node * tree, long long pos) {
	push(tree);
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= pos) {
		auto p = split_size(tree->l, pos);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split_size(tree->r, pos - sz(tree->l) - 1);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

pair <node *, node *> split_val(node * tree, long long val) {
	push(tree);
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
	push(tree);
	if (tree == nullptr)
		return v;
	if (v == nullptr)
		return tree;
	auto p = split_val(tree, v->val);
	p.first = merge(p.first, v);
	tree = merge(p.first, p.second);
	return tree;
}

node * get_pos(node * tree, long long pos) {
	push(tree);
	if (tree == nullptr)
		return nullptr;
	if (sz(tree->l) == pos)
		return tree;
	else if (sz(tree->l) > pos)
		return get_pos(tree->l, pos);
    else
		return get_pos(tree->r, pos - sz(tree->l) - 1);
}

node * stupid_merge(node * tree, node * root) {
	push(tree);
	push(root);
	if (root == nullptr)
		return tree;
	tree = stupid_merge(tree, root->l);
	tree = insert(tree, new node(val(root)));
	tree = stupid_merge(tree, root->r);
	return tree;
}

void wr(node * tree) {
	push(tree);
	if (tree == nullptr)
		return;
	wr(tree->l);
	cout << tree->val << " " << tree->must << endl;
	wr(tree->r);
}

node * upd(node * tree, long long x) {
	auto p = split_val(tree, x);
	push(p.second, -1);
	tree = merge(p.first, p.second);
	return tree;
}

node * tree = nullptr;
long long n, q;

void read() {
	cin >> n;
	for (long long i = 0; i < n; i++) {
		long long x;
		cin >> x;
		tree = insert(tree, new node(x));
	}
}

long long get_cnt(node * tree, long long x) {
	auto p = split_val(tree, x);
	long long ans = sz(p.second);
	tree = merge(p.first, p.second);
	return ans;
}

vector<long long> ans;

void run() {
	cin >> q;
	for (long long test = 0; test < q; test++) {
		long long x;
		cin >> x;
		long long fans = get_cnt(tree, x);
		ans.push_back(fans);
		tree = upd(tree, x);
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