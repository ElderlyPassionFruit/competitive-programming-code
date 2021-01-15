#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int INF = -1e9 - 10;

struct event{
	int x, p, ind;
	event() {}
	event(int a, int b, int c) {
		x = a, p = b, ind = c;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.p, a.ind) < tie(b.x, b.p, b.ind);
}

int n;
vector<event> a;

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(4 * n, INF);
		build(1, 0,)
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return INF;
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

segment_tree tree;

void build() {
	vector<int> x;
	sort(all(a));
	for (auto i : a)
		x.push_back(i.p);
	tree = segment_tree(x);
}

int get_l(int pos) {
	if (tree.get(pos + 1, n - 1) < a[pos].p)
		return -1;
	int l = pos, r = n - 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (tree.get(pos + 1, mid) > a[pos].p)
			r = mid;
		else
			l = mid;
	}
	return r;
}

int get_r(int pos) {
	if (tree.get(0, pos - 1) < a[pos].p)
		return -1;
	int l = 0, r = pos;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (tree.get(mid, pos - 1) > a[pos].p)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int dist(int l, int r) {
	return abs(a[l].x - a[r].x);
}

int solve(int pos) {
	int l = get_l(pos);
	int r = get_r(pos);  
 	if (l == -1 && r == -1) {
		return -1;
	}
	if (l == -1 && r != -1) {
		return a[r].ind + 1;
	}
	if (l != -1 && r == -1) {
		return a[l].ind + 1;
	}

	if (dist(l, pos) == dist(pos, r)) {
		if (a[l].p > a[r].p)
			return a[l].ind + 1;
		else
			return a[r].ind + 1;
	}

	if (dist(l, pos) < dist(pos, r)) {
		return a[l].ind + 1;
	}
	else {
		return a[r].ind + 1;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].p;
		a[i].ind = i;
	}
	
	build();
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[a[i].ind] = solve(i);
	}		
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}














