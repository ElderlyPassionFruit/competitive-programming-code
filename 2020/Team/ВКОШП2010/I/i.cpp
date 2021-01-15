#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
 
struct node{
	node *l, *r;
	int val;
	node () {l = nullptr, r = nullptr, val = 0;}
	node (int x) {
		val = x;
		l = nullptr;
		r = nullptr;
	}
};
 
node * clone(node * tree) {
	node * ans = new node();
	if (tree == nullptr) return nullptr;
	ans -> val = tree->val;
	ans -> l = tree->l;
	ans -> r = tree->r;
	return ans;
}
 
node * build(int l, int r) {
	if (l == r - 1) {
		return new node();
	}
	node * tree = new node();
	int m = (l + r) / 2;
	tree->l = build(l, m);
	tree->r = build(m, r);
	return tree;
}

int get_val(node * tree) {
	if (tree == nullptr) return 0;
	return tree->val;
}

node * upd(node * tree, int tl, int tr, int pos, int val) {
	if (tree == nullptr) return tree;
	if (tl >= pos + 1 || tr <= pos) return tree;
	if (tl == tr - 1) {
		tree = clone(tree);
		tree->val = val;
		return tree;
	}
	int tm = (tl + tr) / 2;
	tree = clone(tree);
	tree->l = upd(tree->l, tl, tm, pos, val);
	tree->r = upd(tree->r, tm, tr, pos, val);
	tree->val = get_val(tree->l) + get_val(tree->r);
	return tree;
}
 
int get(node * tree, int l, int r, int sum) {
	if (tree == nullptr) return -1; 
	if (tree->val < sum) return -1;
	if (l == r - 1) return l;
	int m = (l + r) / 2;
	int ans = get(tree->l, l, m, sum);
	if (ans == -1) {
		ans = get(tree->r, m, r, sum - get_val(tree->l));
	}
	return ans;
}
 
int n, m;
vector<node *> roots;
 
void build(vector<int> a) {
	roots.push_back(build(0, n));
	map<int, int> last;
	for (int i = n - 1; i >= 0; i--) {
		roots.push_back(upd(roots.back(), 0, n, i, 1));
		if (last.count(a[i])) {
			roots[roots.size() - 1] = upd(roots.back(), 0, n, last[a[i]], 0);
		}
		last[a[i]] = i;
	}
	reverse(all(roots));
}
 
int get(int l, int k) {
	return get(roots[l], 0, n, k) + 1;
}
 
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("rollback.in", "r", stdin);
	freopen("rollback.out", "w", stdout);
	cin>>n>>m;
	vector<int> a(n);
	for (auto &i : a)
		cin>>i;
	build(a);
	int q;
	cin>>q;
	int p = 0;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin>>x>>y;
		int l = (x + p) % n;
		int k = (y + p) % m + 1;
		int r = get(l, k);
		cout<<r<<'\n';
		p = r;
	}
	return 0;
}