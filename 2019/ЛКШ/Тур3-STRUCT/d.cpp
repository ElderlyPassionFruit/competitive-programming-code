#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node { 
	int val;
	node * l, * r;
	node() {
		val = 0;
		l = nullptr;
		r = nullptr;
	}
	node(int x) {
		val = x;
		l = nullptr;
		r = nullptr;
	}
};

node * clone(node * x) {
	node * ans = new node();
	ans->val = x->val;
	ans->l = x->l;
	ans->r = x->r;
	return ans;
}

node * build(int l, int r) {
	if (l == r - 1) {
		node * tree = new node(0);
		return tree;
	}
	int m = (l + r) / 2;
	node * tree = new node(0);
	tree->l = build(l, m);
	tree->r = build(m, r);
	return tree;
}

node * upd(node * tree, int tl, int tr, int l, int r, int val) {
	assert(tree != nullptr);
	if (tl >= r || tr <= l) 
		return tree;
	if (tl >= l && tr <= r) {
		tree = clone(tree);
		tree->val += val;
		return tree;
	}
	int tm = (tl + tr) / 2;
	tree = clone(tree);
	tree->l = upd(tree->l, tl, tm, l, r, val);
	tree->r = upd(tree->r, tm, tr, l, r, val);
	tree->val = tree->l->val + tree->r->val;
	return tree;
}

int k;

int get(node * tree1, node * tree2, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return -1;
	if (tree1->val - tree2->val < k) {
		k -= tree1->val - tree2->val;
		return -1;
	}
	if (tl == tr - 1)
		return tl;
	int tm = (tl + tr) / 2;
	int ans = get(tree1->l, tree2->l, tl, tm, l, r);
	if (ans == -1)
		ans = get(tree1->r, tree2->r, tm, tr, l, r);
	return ans;
}

const int MOD = 1e9;

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	int a1, l, m;
	cin >> a1 >> l >> m;
	a[0] = a1;
	for (int i = 1; i < n; i++) {
		a[i] = ((long long)a[i - 1] * l + m) % MOD;
	}
}

long long ans;

void run() {
	ans = 0;
	map <int, int> coord, rev;
	set<int> fbuild;
	for (auto i : a)
		fbuild.insert(i);
	int cnt = 0;
	for (auto i : fbuild){
		coord[i] = cnt;
		rev[cnt] = i;
		cnt++;
	}

	vector<node *> roots;
	roots.push_back(build(0, cnt));
	for (int i = 0; i < n; i++) {
		node * tree = upd(roots.back(), 0, cnt, coord[a[i]], coord[a[i]] + 1, 1);
		roots.push_back(tree);
	}

	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		int g;
		cin >> g;
		int x1, lx, mx;
		cin >> x1 >> lx >> mx;
		int y1, ly, my;
		cin >> y1 >> ly >> my;
		int k1, lk, mk;
		cin >> k1 >> lk >> mk;


		int xg, yg, ig, jg, kg;
		ig = min(x1, y1);
		jg = max(x1, y1);
		kg = k1;
		k = kg;
		int fans = get(roots[jg], roots[ig - 1], 0, cnt, 0, cnt);
		fans = rev[fans];
		ans += fans;

		for (int i = 1; i < g; i++) {
			xg = ((long long)(ig - 1) * lx + mx) % n + 1;
			yg = ((long long)(jg - 1) * ly + my) % n + 1;
			ig = min(xg, yg);
			jg = max(xg, yg);
			kg = ((long long)(kg - 1) * lk + mk) % (jg - ig + 1) + 1;
			k = kg;
			int fans = get(roots[jg], roots[ig - 1], 0, cnt, 0, cnt);
			fans = rev[fans];
			ans += fans;
		}
	}
}

void write() {
	cout << ans << endl;
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
