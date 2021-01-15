#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

const int MAXN = 1e6 + 10;
int pows[MAXN];
int base = MAXN + rnd() % 1000;
int mod = 1e9 + rnd() % 1000;

int add(int a, int b) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int mul(int a, int b) {
	return (long long)a * b % mod;
}

struct node{
	int val, prior, sum, sz;
	node *l, *r;
	node() {
	}
	node(int new_val) {
		val = new_val;
		prior = rnd();
		sum = mul(val, pows[val]);
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
};

void wr(node * tree) {
	if (tree == nullptr)
		return;
	wr(tree->l);
	cout << tree->val << " " << tree->sum << endl;
	wr(tree->r);
}

int sum(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sum;
}

int sz(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr) return;
	tree->sum = add(add(sum(tree->l), sum(tree->r)), mul(tree->val, pows[tree->val])); 
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

pair <node *, node *> split(node * tree, int key) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->val > key) {
		auto p = split(tree->l, key);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, key);
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
		if (tree->val > x->val)
			tree->l = insert(tree->l, x);
		else
			tree->r = insert(tree->r, x);
		upd(tree);
		return tree;
	}
}

node * erase(node * tree, int x) {
	if (tree == nullptr)
		return nullptr;
	if (tree->val == x)
		return merge(tree->l, tree->r);
	if (tree->val > x) {
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

int p[MAXN], q[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		q[i] = p[i];
	}
	sort(q, q + n);
}

int par[MAXN];
vector<int> v[MAXN];
node * roots[MAXN];
node * sorted_roots[MAXN];
int cnt_have;

void build() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows[i] = mul(pows[i - 1], base);
	for (int i = 0; i < n; i++) {
		par[i] = i;
		roots[i] = new node(p[i]);
		sorted_roots[i] = new node(q[i]);
		v[i].push_back(i);
		cnt_have += sum(roots[i]) == sum(sorted_roots[i]);
	}
}

void q_swap(int a, int b) {
	if (par[a] == par[b]) {
		swap(p[a], p[b]);
		return;
	}
	if (sum(roots[par[a]]) == sum(sorted_roots[par[a]])) {
		cnt_have -= sz(roots[par[a]]);
	}
	if (sum(roots[par[b]]) == sum(sorted_roots[par[b]])) {
		cnt_have -= sz(roots[par[b]]);
	}
	roots[par[a]] = erase(roots[par[a]], p[a]);
	roots[par[a]] = insert(roots[par[a]], new node(p[b]));
	
	roots[par[b]] = erase(roots[par[b]], p[b]);
	roots[par[b]] = insert(roots[par[b]], new node(p[a]));
	if (sum(roots[par[a]]) == sum(sorted_roots[par[a]])) {
		cnt_have += sz(roots[par[a]]);
	}
	if (sum(roots[par[b]]) == sum(sorted_roots[par[b]])) {
		cnt_have += sz(roots[par[b]]);
	}
	swap(p[a], p[b]);
}

void add_pair(int a, int b) {
	if (par[a] == par[b]) return;
	if (sz(roots[par[a]]) < sz(roots[par[b]])) swap(a, b);
	if (sum(roots[par[a]]) == sum(sorted_roots[par[a]])) {
		cnt_have -= sz(roots[par[a]]);
	}
	if (sum(roots[par[b]]) == sum(sorted_roots[par[b]])) {
		cnt_have -= sz(roots[par[b]]);
	}
	for (auto i : v[par[b]]) {
		par[i] = par[a];
		roots[par[a]] = insert(roots[par[a]], new node(p[i]));
		sorted_roots[par[a]] = insert(sorted_roots[par[a]], new node(q[i]));
		v[par[a]].push_back(i);
	}
	if (sum(roots[par[a]]) == sum(sorted_roots[par[a]])) {
		cnt_have += sz(roots[par[a]]);
	}
	par[b] = par[a];
}

bool check() {
	return cnt_have == n;
}

int get() {
	return 1;
}

void write() {
	cout << "par = " << endl;
	for (int i = 0; i < n; i++) {
		cout << par[i] << " ";
	}
	cout << endl;
	
	cout << "v = " << endl;
	for (int i = 0; i < n; i++) {
		if (par[i] != i) continue;
		cout << "i = " << i << endl;
		for (auto j : v[i])
			cout << j << " ";
		cout << endl;
	}

	cout << "roots = " << endl;
	for (int i = 0; i < n; i++) {
		if (par[i] != i) continue;
		cout << "i = " << i << endl;
		wr(roots[i]);
		//cout << endl;
	}
	cout << endl;
	cout << "sorted = " << endl;
	for (int i = 0; i < n; i++) {
		if (par[i] != i) continue;
		cout << "i = " << i << endl;
		wr(sorted_roots[i]);
		//cout << endl;
	}
	cout << endl;
	cout << "cnt_have = " << cnt_have << endl;
}

void run() {
	build();
	/*cout << "p = " << endl;
	for (int i = 0; i < n; i++)
		cout << p[i] << " ";
	cout << endl;
	cout << "q = " << endl;
	for (int i = 0; i < n; i++)
		cout << q[i] << " ";
	cout << endl;*/

	for (int test = 0; test < m; test++) {
		int type;
		cin >> type;
		if (type == 1) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			q_swap(a, b);
		}
		else if (type == 2) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			add_pair(a, b);
		}
		else if (type == 3) {
			if (check()) {
				cout << "DA" << "\n";
			}
			else {
				cout << "NE" << "\n";
			}
		}
		else if (type == 4) {
			cout << get() << "\n";
		}
		//write();
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