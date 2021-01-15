#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int a[MAXN];

struct node{
	int val;
	node * l, * r;
	node (int x) {
		val = x;
		l = nullptr;
		r = nullptr;
	}
};

node * clone(node * tree) {
	node * ans = new node(0);
	ans->val = tree->val;
	ans->l = tree->l;
	ans->r = tree->r;
	return ans;
}

node * build(int l, int r) {
	if (l == r - 1) {
		node * tree = new node(a[l]);
		return tree;
	}
	int m = (l + r) / 2;
	node * tree = new node(0);
	tree->l = build(l, m);
	tree->r = build(m, r);
	return tree;
}

int get(node * tree, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l)
		return 0;
	if (tl >= l && tr <= r)
		return tree->val;
	int tm = (tl + tr) / 2;
	return max(get(tree->l, tl, tm, l, r), get(tree->r, tm, tr, l, r));
}

node * upd(node * tree, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l)
		return tree;
	if (tl >= l && tr <= r) {
		tree = clone(tree);
		tree->val = val;
		return tree;
	}
	int tm = (tl + tr) / 2;
	tree = clone(tree);
	tree->l = upd(tree->l, tl, tm, l, r, val);
	tree->r = upd(tree->r, tm, tr, l, r, val);
	return tree;
}

int n;
vector<node *> root;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	root.push_back(build(0, n));
}

vector<int> ans;

void run() {
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		string type;
		cin >> type;
		if (type == "create") {
			int pos1, pos2, x;
			cin >> pos1 >> pos2 >> x;
			pos1--;
			pos2--;
			root.push_back(upd(root[pos1], 0, n, pos2, pos2 + 1, x));
		}
		if (type == "get") {
			int pos1, pos2;
			cin >> pos1 >> pos2;
			pos1--;
			pos2--;
			ans.push_back(get(root[pos1], 0, n, pos2, pos2 + 1));
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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