#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

mt19937 rnd(time(0));

struct node{
	node *l, *r, *p;
	bool left;
	bool reverse;
	int sz, val, prior, sum, ed;
	node() {}
	node(int new_val) {
		l = nullptr;
		r = nullptr;
		p = nullptr;
		left = false;
		reverse = false;
		sz = 1;
		sum = 0;
		ed = 0;
		val = new_val;
		prior = rnd();
	}
};

int sz(node * tree) {
	if (tree == nullptr) return 0;
	return tree->sz;
}

int sum(node * tree) {
	if (tree == nullptr) return 0;
	return tree->sum;
}

void push(node * tree) {
	if (tree == nullptr) return;
	if (tree->reverse == false) return;
	tree->reverse = false;
	swap(tree->l, tree->r);
	if (tree->l != nullptr) {
		tree->l->left = true;
		tree->l->reverse ^= 1;
	}
	if (tree->r != nullptr) {
		tree->r->left = false;
		tree->r->reverse ^= 1;
	}	
}

void upd(node * tree) {
	if (tree == nullptr) return;
	tree->sz = sz(tree->l) + sz(tree->r) + 1;
	tree->p = nullptr;
	tree->left = false;
	tree->sum = sum(tree->l) + sum(tree->r) + tree->ed;
	if (tree->l != nullptr) {
		tree->l->p = tree;
		tree->l->left = true;
	}
	if (tree->r != nullptr) {
		tree->r->p = tree;
		tree->r->left = false;
	}
}

node * merge(node * tree_l, node * tree_r) {
	push(tree_l);
	push(tree_r);
	if (tree_l == nullptr) return tree_r;
	if (tree_r == nullptr) return tree_l;
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

pair<node *, node*> split(node * tree, int size) {
	push(tree);
	if (tree == nullptr) return {nullptr, nullptr};
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

int val(node * tree) {
	if (tree == nullptr) return -1;
	return tree->val;
}

node * get_root(node * tree) {
	if (tree->p == nullptr) return tree;
	return get_root(tree->p);
}

int get_pos(node * tree) {
	bool flag = false;
	int ans = 0;
	node * root = tree;
	vector<bool> st;
	while (root->p != nullptr) {
		st.push_back(root->left);
		root = root->p;
	}
	while (!st.empty()) {
		st[st.size() - 1] = (st[st.size() - 1] ^ (root->reverse));
		push(root);
		if (st.back())
			root = root->l;
		else
			root = root->r;
		st.pop_back();
	}
	push(tree);
	while (tree != nullptr) {
		if (!flag) {
			ans += sz(tree->l) + 1;
		}
		flag = tree->left;
		tree = tree->p;
	}
	return ans;
}

node * get_left(node * tree) {
	push(tree);
	if (tree == nullptr) return nullptr;
	if (tree->l == nullptr) return tree;
	return get_left(tree->l);
}

void full_upd(node * tree) {
	while (tree != nullptr) {
		tree->sum = sum(tree->l) + sum(tree->r) + tree->ed;
		tree = tree->p;
	}
}

int n, m, q;

void read() {
	cin >> n >> m >> q;
}

vector<int> ans;
vector<node *> pos;

void build() {
	for (int i = 0; i < n; i++) {
		pos.push_back(new node(i));
	}
}

void add(int u, int v) {
	pos[u]->ed++;
	pos[v]->ed++;
	full_upd(pos[u]);
	full_upd(pos[v]);
	node * r1 = get_root(pos[u]);
	node * r2 = get_root(pos[v]);
	if (r1->val == r2->val) {
		return;
	}
	if (get_left(r1)->val == u) {
		r1->reverse ^= 1;
	}
	if (get_left(r2)->val != v) {
		r2->reverse ^= 1;
	}
	merge(r1, r2);
}

void del(int u, int v) {
	pos[u]->ed--;
	pos[v]->ed--;
	full_upd(pos[u]);
	full_upd(pos[v]);
	node * r1 = get_root(pos[u]);
	int pos_u = get_pos(pos[u]);
	int pos_v = get_pos(pos[v]);
	if (pos_u > pos_v) swap(pos_u, pos_v);
	if (pos_v - pos_u == 1) {
		auto x = split(r1, min(pos_u, pos_v));
		if (sum(x.first) + sum(x.second) == 2 * (sz(x.first) + sz(x.second) - 1)) {
			merge(x.second, x.first);
		}
	}
}

int get(int u, int v) {
	node * r1 = get_root(pos[u]);
	node * r2 = get_root(pos[v]);
	if (r1->val != r2->val) return -1;
	int pos_u = get_pos(pos[u]);
	int pos_v = get_pos(pos[v]);
	int ans = abs(pos_u - pos_v);
	if (sum(r1) == 2 * sz(r1)) {
		ans = min(ans, sz(r1) - ans);
	}
	return max(ans - 1, 0);
}

void run() {
	build();
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		add(u, v);
	}

	for (int i = 0; i < q; i++) {
		char type;
		int u, v;
		cin >> type >> u >> v;
		u--;
		v--;
		if (type == '+')
			add(u, v);
		else if (type == '-')
			del(u, v);
		else
			ans.push_back(get(u, v));
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}