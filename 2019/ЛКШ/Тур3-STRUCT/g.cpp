#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
 
#include <bits/stdc++.h>
 
using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
struct node{
	int val, sz;
	node *l, *r;
	node(int x) {
		val = x;
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
 
	~node() {
		delete l;
		delete r;
	}
};
 
node * clone(node * tree) {
	node * ans = new node(0);
	ans->val = tree->val;
	ans->sz = tree->sz;
	ans->l = tree->l;
	ans->r = tree->r;
	return ans;
}
 
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
 
mt19937 rnd(time(0) + 228 + 1337);
 
node * merge(node * tree_l, node * tree_r, bool flag) {
	if (tree_l == nullptr)
		return tree_r;
	if (tree_r == nullptr)
		return tree_l;
	if (rnd() % (tree_l->sz + tree_r->sz) < tree_l->sz) {
		if (flag)
		tree_l = clone(tree_l);
		tree_l->r = merge(tree_l->r, tree_r, flag);
		upd(tree_l);
		return tree_l;
	}
	else {
		if (flag)
		tree_r = clone(tree_r);
		tree_r->l = merge(tree_l, tree_r->l, flag);
		upd(tree_r);
		return tree_r;
	}
}
 
pair <node *, node *> split(node * tree, int size) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= size) {
		tree = clone(tree);
		auto p = split(tree->l, size);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		tree = clone(tree);
		auto p = split(tree->r, size - sz(tree->l) - 1);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}
 
struct event{
	int cnt, from, to;
};
 
int n, m;
vector<event> q;
node * tree = nullptr;
 
void read() {
	cin >> n >> m;
	q.resize(m);
	for (auto &i : q)
		cin >> i.cnt >> i.from >> i.to;
}
 
node * get(node * tree, int l, int r) {
	auto x = split(tree, r);
	auto y = split(x.first, l - 1);
	auto help = y.second;
 
	x.first = merge(y.first, y.second, true);
	tree = merge(x.first, x.second, true);
	return help;
}
 
node * insert(node * tree, node * v, int l, int r) {
	auto x = split(tree, r);
	auto y = split(x.first, l - 1);
	//delete y.second;
	x.first = merge(y.first, v, true);
	tree = merge(x.first, x.second, true);
	return tree;
}
 
vector<int> ans;
 
void make_ans(node * tree) {
	if (tree == nullptr)
		return;
	make_ans(tree->l);
	ans.push_back(tree->val);
	make_ans(tree->r);
}
 
void run() {
	for (int i = 0; i < n; i++) {
		tree = merge(tree, new node(i + 1), false);
	}	
	reverse(q.begin(), q.end());
	for (int i = 0; i < m; i++) {
		int cnt = q[i].cnt;
		int from = q[i].from;
		int to = q[i].to;
 
		int l = to, r = to + cnt - 1;
		auto help = get(tree, l, r);
 
		l = from, r = from + cnt - 1;
		tree = insert(tree, help, l, r);
	}
	make_ans(tree);
}
 
void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}
 
signed main() {
	//freopen("balls.in", "r", stdin);
	//freopen("balls.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}