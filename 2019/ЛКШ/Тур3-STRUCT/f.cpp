#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int val, pos;
	node *l, *r;
	node() {
		val = 0;
		pos = 0;
		l = nullptr;
		r = nullptr;
	}
};

node * merge(node * tree) {
	if (tree->l->val <= tree->r->val) {
		tree->val = tree->l->val;
		tree->pos = tree->l->pos;
	}
	else {
		tree->val = tree->r->val;
		tree->pos = tree->r->pos;
	}
	return tree;
}

node * build(int l, int r) {
	if (l == r - 1) {
		node * tree = new node();
		tree->pos = l;
		return tree;
	}
	int m = (l + r) / 2;
	node * tree = new node();
	tree->l = build(l, m);
	tree->r = build(m, r);
	tree = merge(tree);
	return tree; 
}

node * clone(node * tree) {
	node * ans = new node();
	ans->val = tree->val;
	ans->pos = tree->pos;
	ans->l = tree->l;
	ans->r = tree->r;
	return ans;
}

node * upd(node * tree, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) return tree;
	if (tl >= l && tr <= r) {
		//cerr << "val = " << val << endl;
		tree = clone(tree);
		tree->val =  max(tree->val, val);
		return tree;
	}
	int tm = (tl + tr) / 2;
	tree = clone(tree);
	tree->l = upd(tree->l, tl, tm, l, r, val);
	tree->r = upd(tree->r, tm, tr, l, r, val);
	tree = merge(tree);
	return tree;
}

int get(node * tree, int tl, int tr, int num) {
	if (tree->val > num) 
		return -1;
	if (tl == tr - 1) 
		return tree->pos;
	
	int tm = (tl + tr) / 2;
	int ans = get(tree->l, tl, tm, num);

	if (ans == -1) 
		ans = get(tree->r, tm, tr, num);
	return ans;
}

int n, tikets, m, q;

vector<pair <pair <int, int>, int>> a;
vector<pair <int, int> > query;

void read() {
	cin >> n >> tikets >> m;
	for (int i = 0; i < m; i++) {
		int c, s, f;
		cin >> c >> s >> f;
		c--;
		a.push_back({{s, f}, c});
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		int s, f;
		cin >> s >> f;
		query.push_back({s, f});
	}
}

vector<int> ans;

void run() {
	set<int> help;
	vector<int> pos;
	for (auto i : a) {
		help.insert(i.first.first);
		help.insert(i.first.second);
	}

	int cnt = 0;
	map <int, int> coord;
	for (auto i : help) {
		coord[i] = cnt;
		pos.push_back(i);
	}

	vector<node *> roots;
	roots.push_back(build(0, tikets));

	map <int, vector<pair <int, int> > > ends;
	for (auto i : a) {
		ends[i.first.first].push_back({i.first.second, i.second});
	}

	for (auto x : coord) {
	 	auto i = ends[x.first];
		node * tree = roots.back();
		for (auto j : i) {
			tree = upd(tree, 0, tikets, j.second, j.second + 1, j.first);
		}
		roots.push_back(tree);
	}

	int p = 0;

	for (int i = 0; i < q; i++) {
		int s = query[i].first + p;
		int f = query[i].second + p;
		int pos_s = s;
		int pos_f = lower_bound(pos.begin(), pos.end(), f) - pos.begin();
		int fans = get(roots[pos_f], 0, tikets, pos_s);
		ans.push_back(fans + 1);
		p = fans + 1;
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
}

signed main() {
	freopen("intercity.in", "r", stdin);
	freopen("intercity.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
} 