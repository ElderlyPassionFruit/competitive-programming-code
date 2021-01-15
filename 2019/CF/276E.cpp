#include <bits/stdc++.h>

using namespace std;
#define int long long

struct node{
	int pref, suff, ans;
	bool flag;
	node *l, *r;
	node(int val) {
		pref = val;
		suff = val;
		ans = val;
		flag = (val == 1);
		l = nullptr;
		r = nullptr;
	}
};

node * merge(node * a, node * b) {
	node * ans = new node(0);
	if (a->flag && b->flag) {
		ans->flag = true;
		ans->l = a;
		ans->r = b;
		ans->pref = a->ans + b->ans;
		ans->suff = a->ans + b->ans;
		ans->ans = a->ans + b->ans;
		return ans;
	}
	ans->flag = false;
	ans->l = a;
	ans->r = b;
	ans->pref = a->pref;
	ans->suff = b->suff;
	ans->ans = max(a->suff + b->pref, max(a->ans, b->ans));
	return ans;
}

node * clone(node * tree) {
	node * ans = new node(0);
	ans->flag = tree->flag;
	ans->l = tree->l;
	ans->r = tree->r;
	ans->pref = tree->pref;
	ans->suff = tree->suff;
	ans->ans = tree->ans;
	return ans;
}

node * build(int l, int r) {
	if (l == r - 1) {
		node * tree = new node(0);
		return tree;
	}
	int m = (l + r) / 2;
	node * L = build(l, m);
	node * R = build(m, r);
	node * tree = merge(L, R);
	return tree;
}

node * upd(node * tree, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) return tree;
	if (tl >= l && tr <= r) {
		tree = clone(tree);
		tree = new node(val);
		cout << "tree = " << tree->ans << endl;
		return tree;
	}

	int tm = (tl + tr) / 2;
	tree = clone(tree);
	node * L = upd(tree->l, tl, tm, l, r, val);
	node * R = upd(tree->r, tm, tr, l, r, val);
	tree = merge(L, R);
	cout << "tree = " << tree->ans << endl;
	return tree;	
}

node * get(node * tree, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return new node(0);
	if (tl >= l && tr <= r) return clone(tree);
	int tm = (tl + tr) / 2;
	return merge(get(tree->l, tl, tm, l, r), get(tree->r, tm, tr, l, r));
}

int n, m;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

vector<int> ans;
vector<node*> roots;
void run() {
	set<int> help;
	for (auto i : a)
		help.insert(i);
	
	map<int, int> coords;
	map<int, int> fans;
	int cnt = 0;
	for (auto i : help){
		fans[cnt] = i;
		coords[i] = cnt;
		cnt++;
	}

	map<int, vector<int> > nums;
	for (int i = 0; i < n; i++) {
		nums[coords[a[i]]].push_back(i);
	}

	cout << "coords = " << endl;
	for (auto i : coords)
		cout << i.first << " " << i.second << endl;
	cout << "fans = " << endl;
	for (auto i : fans)
		cout << i.first << " " << i.second << endl;
	cout << "nums = " << endl;
	for (auto i : nums) {
		cout << "i = " << i.first << endl;
		for (auto j : i.second)
			cout << j << " ";
		cout << endl;
	} 

	roots.push_back(build(0, n));

	for (int i = cnt - 1; i >= 0; i--) {
		node * tree = clone(roots.back());
		for (auto j : nums[i])
			upd(tree, 0, n, j, j + 1, 1);
		roots.push_back(tree);
	}

	cout << "roots.size() = " << roots.size() << endl;
	cout << "roots = " << endl;
	for (auto i : roots) {
		cout << i->ans << endl;
	}
	cout << endl;
	cout << get(roots.back(), 0, n, 4, 5)->ans << endl;

	cin >> m;
	for (int test = 0; test < m; test++) {
		int l, r, w;
		cin >> l >> r >> w;
		l--;
		r--;


		int l1 = 0, r1 = cnt;
		while (l1 < r1 - 1) {
			int mid1 = (l1 + r1) / 2;
			node * help_ans = get(roots[mid1], 0, n, l, r + 1);
			if (help_ans->ans >= w)
				r1 = mid1;
			else
				l1 = mid1;
		}
		r1--;
		ans.push_back(fans[r1]);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
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