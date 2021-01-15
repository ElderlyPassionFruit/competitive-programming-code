#include <bits/stdc++.h>

using namespace std;

struct node{
	int val, pos, prior, sz, must;
	node *l, *r;
	node (int new_val, int new_pos) {
		val = new_val;
		pos = new_pos;
		prior = (rand() << 16) | rand();
		must = 0;
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
};

int n, q;
node * tree;

int sz(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

int must(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->must;
}

void upd(node * tree) {
	if (tree == nullptr)
		return;
	tree->sz = 1 + sz(tree->l) + sz(tree->r);
}

void push(node * tree, int must) {
	if (tree == nullptr)
		return;
	tree->must += must;
}

void push(node * tree) {
	if (tree == nullptr)
		return;
	tree->val += tree->must;
	push(tree->l, tree->must);
	push(tree->r, tree->must);
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

pair <node *, node *> split(node * tree, int pos) {
	push(tree);
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->pos >= pos) {
		auto p = split(tree->l, pos);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, pos);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

node * insert(node * tree, int pos, node * new_val) {
	auto p = split(tree, pos);
	p.first = merge(p.first, new_val);
	tree = merge(p.first, p.second);
	return tree;
}

node * erase(node * tree, int pos) {
	auto p = split(tree, pos);
	auto j = split(p.second, pos + 1);
	tree = merge(p.first, j.second);
	return tree;
}

node * left(node * tree) {
	push(tree);
	if (tree == nullptr)
		return nullptr;
	if (tree->l != nullptr)
		return left(tree->l);
	return tree;
}

node * val(node * tree, int pos) {
	auto p = split(tree, pos);
	auto ans = left(p.second);
	tree = merge(p.first, p.second);
	return ans;
}


void read() {
	cin >> n >> q;
	tree = nullptr;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x > 1) {
			tree = insert(tree, i, new node(x, i));
		}
	}
}

void add(int l, int r) {
	auto p = split(tree, l);
	auto j = split(p.second, r + 1);
	if (j.first != nullptr)
		j.first->must--;
	p.second = merge(j.first, j.second);
	tree = merge(p.first, p.second);
}


int now;
int ans;

node * get_ans(node * tree) {
	push(tree);

	if (now == 0)
		return tree;

	if (tree == nullptr)
		return nullptr;

	tree->l = get_ans(tree->l);

	if (tree->val <= 1) {
		tree->r = get_ans(tree->r);
		tree = merge(tree->l, tree->r);
		return tree;
	}
	if (now == 0)
		return tree;

	now /= tree->val;
	if (now == 0)
		ans = tree->pos + 1;

	tree->r = get_ans(tree->r);
	return tree;
}


int solve(int l, int r, int x) {
	auto p = split(tree, l);
	auto j = split(p.second, r + 1);
	now = x;
	j.first = get_ans(j.first);
	if (now > 0)
		ans = -1;
	p.second = merge(j.first, j.second);
	tree = merge(p.first, p.second);
	return ans;
}

void run() {
	for (int test = 0; test < q; test++) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			add(l, r);
		}
		if (type == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			r--;
			cout << solve(l, r, x) << "\n";
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}