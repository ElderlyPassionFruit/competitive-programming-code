#include <bits/stdc++.h>

using namespace std;
#define int long long

struct node{
	int val, prior, sz, max, fans;
	node *l, *r;
	node(int new_val, int new_fans) {
		fans = new_fans;
		val = new_val;
		max = new_val;
		sz = 1;
		prior = (rand() << 16) | rand();
		l = nullptr;
		r = nullptr;
	}
};

const int INF = -1e18;

int max(node * tree) {
	if (tree == nullptr)
		return INF;
	return tree->max;
}

int sz(node * tree) {
	if (tree== nullptr)
		return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr)
		return;
	tree->sz = 1 + sz(tree->l) + sz(tree->r);
	tree->max = max(tree->val, max(max(tree->l), max(tree->r)));
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

pair <node*, node*> split(node * tree, int size) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= size) {
		auto p = split(tree->l, size);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, size - sz(tree->l) - 1);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

node * insert(node * tree, int pos, node * val) {
	auto p = split(tree, pos);
	p.first = merge(p.first, val);
	tree = merge(p.first, p.second);
	return tree;
}


int max(node * tree, int r) {
	auto p = split(tree, r);
	int ans = max(p.first);
	tree = merge(p.first, p.second);
	return ans;
}


int n;

void read() {
	cin >> n;
}

vector <int> ans;

void wr(node * tree) {
	if (tree == nullptr)
		return;
	wr(tree->l);
	ans.push_back(tree->fans);
	wr(tree->r);
}


void run() {
	node * help = nullptr;
	int pos = 1;
	for (int test = 0; test < n; test++) {
		pair <int, int> i;
		cin >> i.first >> i.second;
		int l = 0, r = min(i.second + 1, sz(help) + 1);
	
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (max(help, mid) < i.first)
				l = mid;
			else
				r = mid;
		}
		help = insert(help, l, new node(i.first, pos++));
	}
	wr(help);
}

void write() {
	reverse(ans.begin(), ans.end());
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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