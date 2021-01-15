#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = -1e9;
struct node{
	int prior, val, sz, max, must;
	node *l, *r;
	node() {
	
	}
	node(int new_val) {
		prior = (rand() << 16) | rand();
		l = nullptr;
		r = nullptr;
		val = new_val;
		max = val;
		sz = 1;
		must = 0;
	}
};

int must(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->must;
}

int val(node * tree) {
	if (tree == nullptr)
		return INF;
	return tree->val + tree->must;
}

int max(node * tree) {
	if (tree == nullptr)
		return INF;
	return tree->max;
}

int sz(node * tree) {
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

void push(node * tree, int must) {
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

pair <node *, node *> split_size(node * tree, int pos) {
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

pair <node *, node *> split_val(node * tree, int val) {
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

node * get_pos(node * tree, int pos) {
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
	//push(tree);
	push(root);
	if (root == nullptr)
		return tree;
	tree = stupid_merge(tree, root->l);
	tree = insert(tree, new node(val(root)));
	tree = stupid_merge(tree, root->r);
	return tree;
}

node * upd(node * tree, int x) {
	auto p = split_val(tree, x);
	auto v = split_val(p.second, 2 * x);
	push(v.second, -x + 1);
	push(v.first, -x + 1);
	p.first = stupid_merge(p.first, v.first);
	tree = merge(p.first, v.second);
	return tree;
}

void wr(node * tree) {
	//push(tree);
	if (tree == nullptr)
		return;
	wr(tree->l);
	cout << tree->val << " " << tree->must << endl;
	wr(tree->r);
}

void print(node * tree) {
	cout << "tree = ";
	wr(tree);
	cout << endl;
}


node * tree = nullptr;
int n, q;

void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		tree = insert(tree, new node(x));
	}
}

void run() {
	//print(tree);
	for (int test = 0; test < q; test++) {
		int type;
		cin >> type;
		if (type == 1) {
			int pos;
			cin >> pos;
			pos--;
			node * ans = get_pos(tree, pos);
			cout << val(ans) << " ";
		}
		if (type == 2) {
			int x;
			cin >> x;
			x++;
			tree = upd(tree, x);
		}
		//print(tree);
	}
}

void write() {

}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}