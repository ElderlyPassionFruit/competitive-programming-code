#include <bits/stdc++.h>

using namespace std;
#define int long long

struct node{
	int val, prior, sz;
	node * l, * r;
	node (int new_val) {
		val = new_val;
		prior = (rand() << 16) | rand();
		l = nullptr;
		r = nullptr;
		sz = 1;
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

pair <node *, node *> split(node * tree, int size) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= size) {
		auto p = split(tree->l, size);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, size - 1 - sz(tree->l));
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

node * erase(node * tree, int pos) {
	auto p = split(tree, pos);
	auto j = split(p.second, 1);
	tree = merge(p.first, j.second);
	return tree;
}

node * get_pos(node * tree, int pos) {
	auto p = split(tree, pos);
	auto j = split(p.second, 1);
	auto ans = j.first;
	p.second = merge(j.first, j.second);
	tree = merge(p.first, p.second);
	return ans;
}


void wr(node * tree) {
	if (tree == nullptr)
		return;
	wr(tree->l);
	cout << tree->val << " ";
	wr(tree->r);
}

int n;
string s;
int m;
node * tree;
vector<pair <pair <int, int>, int> > help;

void read() {
	cin >> s;
	n = s.size();
	tree = nullptr;
	for (int i = 0; i < n; i++) {
		tree = insert(tree, i, new node(s[i] - '0'));
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		help.push_back({{a, b}, i});
	}
	sort(help.begin(), help.end());
	reverse(help.begin(), help.end());
}

vector<int> ans;

void run() {
	ans.resize(m);
	int pos_tree = 0;
	int pos_have = 0;
	while (pos_have < m) {
		while (sz(tree) > help[pos_have].first.first) {
			if (pos_tree == sz(tree) - 1) {
				tree = erase(tree, pos_tree);
				pos_tree--;
				continue;
			}
			auto n1 = get_pos(tree, pos_tree);
			auto n2 = get_pos(tree, pos_tree + 1);
			if (n1->val >= n2->val) {
				pos_tree++;
				continue;
			}
			tree = erase(tree, pos_tree);
			pos_tree--;
			pos_tree = max(pos_tree, 0LL);
		}

		ans[help[pos_have].second] = get_pos(tree, help[pos_have].first.second - 1)->val;

		pos_have++;
	}
}

void write() {
	for (auto i : ans)
		cout << i;
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