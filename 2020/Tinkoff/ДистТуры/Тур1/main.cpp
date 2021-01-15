#include <bits/stdc++.h>
  
using namespace std;
 
mt19937 rnd(time(0));
const int INF = 1e9 + 228;
const int MAXN = 1e6 + 10;
int pows1[MAXN];
int pows2[MAXN]; 
int pows 	INF +  rand() % 100000;
int base2 = MAXN + rand() % 100000;
int base3 = 179;
int mod1 = 1e9 + 7;
int mod2 = 998244353;
int mod3 = 1e9 + 9 + rand() % 100000;

int add(int a, int b, int mod) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int sub(int a, int b, int mod) {
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

int mul(int a, int b, int mod) {
	return (long long)a * b % mod;
}

struct node{
	int val, prior, sum1, sum2, sum3, sz;
	node *l, *r;
	node() {
	}
	node(int new_val) {
		val = new_val;
		prior = rnd();
		sum1 = mul(1, pows1[val], mod1);
		sum2 = mul(1, pows2[val], mod2);	
		sum3 = mul(1, pows3[val], mod3);
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
};

void wr(node * tree) {
	if (tree == nullptr)
		return;
	wr(tree->l);
	cout << tree->val << " " << tree->sum1 << " " << tree->sum2 << " " << tree->prior << endl;
	wr(tree->r);
}

int sum1(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sum1;
}

int sum2(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sum2;
}

int sum3(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sum3;
}

int sz(node * tree) {
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr) return;
	tree->sum1 = add(add(sum1(tree->l), sum1(tree->r), mod1), mul(1, pows1[tree->val], mod1), mod1); 
	tree->sum2 = add(add(sum2(tree->l), sum2(tree->r), mod2), mul(1, pows2[tree->val], mod2), mod2); 
	tree->sum3 = add(add(sum3(tree->l), sum3(tree->r), mod3), mul(1, pows3[tree->val], mod3), mod3); 
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
long long fans;
map <int, int> hashs;

void add_hash(int i) {
	int x1 = sub(sum1(roots[i]), sum1(sorted_roots[i]), mod1);
	int x2 = sub(sum2(roots[i]), sum2(sorted_roots[i]), mod2);
	int x3 = sub(sum3(roots[i]), sum3(sorted_roots[i]), mod3);
	if (x1 != 0 && x2 != 0 && x3 != 0) {
		hashs[x1 + x2 + x3] += sz(roots[par[i]]);
		int x = sub(0, x1, mod1) + sub(0, x2, mod2) + sub(0, x3, mod3);
		if (hashs.count(x)) {
			fans += (long long)hashs[x] * sz(roots[par[i]]);
		}
	}
}

void del_hash(int i) {
	int x1 = sub(sum1(roots[i]), sum1(sorted_roots[i]), mod1);
	int x2 = sub(sum2(roots[i]), sum2(sorted_roots[i]), mod2);
	int x3 = sub(sum3(roots[i]), sum3(sorted_roots[i]), mod3);
	if (x1 != 0 && x2 != 0 && x3 != 0) {
		hashs[x1 + x2 + x3] -= sz(roots[par[i]]);
		if (hashs[x1 + x2 + x3] == 0)
			hashs.erase(x1 + x2 + x3);
		int x = sub(0, x1, mod1) + sub(0, x2, mod2) + sub(0, x3, mod3);
		if (hashs.count(x)) {
			fans -= (long long)hashs[x] * sz(roots[par[i]]);
		}
	}
}

void add_have(int i) {
	if (sum1(roots[i]) == sum1(sorted_roots[i]) && sum2(roots[i]) == sum2(sorted_roots[i]) && sum3(roots[i]) == sum3(sorted_roots[i])) {
		cnt_have += sz(roots[i]);
	}
}

void del_have(int i) {
	if (sum1(roots[i]) == sum1(sorted_roots[i]) && sum2(roots[i]) == sum2(sorted_roots[i]) && sum3(roots[i]) == sum3(sorted_roots[i])) {
		cnt_have -= sz(roots[i]);
	}
}

void build() {
	pows1[0] = 1;
	pows2[0] = 1;
	pows3[0] = 1;
	for (int i = 1; i < MAXN; i++){
		pows1[i] = mul(pows1[i - 1], base1, mod1);
		pows2[i] = mul(pows2[i - 1], base2, mod2);
		pows3[i] = mul(pows3[i - 1], base3, mod3);
	}

	fans = 0;
	for (int i = 0; i < n; i++) {
		par[i] = i;
		roots[i] = new node(p[i]);
		sorted_roots[i] = new node(q[i]);
		v[i].push_back(i);
		add_have(i);
		add_hash(i);
	}
}

void q_swap(int a, int b) {
	if (par[a] == par[b]) {
		swap(p[a], p[b]);
		return;
	}
	del_have(par[a]);
	del_have(par[b]);

	del_hash(par[a]);
	del_hash(par[b]);

	roots[par[a]] = erase(roots[par[a]], p[a]);
	roots[par[a]] = insert(roots[par[a]], new node(p[b]));
	
	roots[par[b]] = erase(roots[par[b]], p[b]);
	roots[par[b]] = insert(roots[par[b]], new node(p[a]));
	
	add_have(par[a]);
	add_have(par[b]);

	add_hash(par[a]);
	add_hash(par[b]);

	swap(p[a], p[b]);
}

void add_pair(int a, int b) {
	if (par[a] == par[b]) return;
	if (sz(roots[par[a]]) < sz(roots[par[b]])) swap(a, b);
	del_have(par[a]);
	del_have(par[b]);

	del_hash(par[a]);
	del_hash(par[b]);

	for (auto i : v[par[b]]) {
		if (i != b) 
		par[i] = par[a];
		roots[par[a]] = insert(roots[par[a]], new node(p[i]));
		sorted_roots[par[a]] = insert(sorted_roots[par[a]], new node(q[i]));
		v[par[a]].push_back(i);
	}

	v[par[b]].clear();
	delete roots[par[b]];
	delete sorted_roots[par[b]];
	par[b] = par[a];

	add_have(par[a]);
	add_hash(par[a]);
}

bool check() {
	return cnt_have == n;
}

long long get() {
	return fans;
}

void run() {
	build();

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
	}
}

signed main() {
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}