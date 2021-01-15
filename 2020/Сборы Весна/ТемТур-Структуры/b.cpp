#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int val, l, r;
	node() {
		val = 0, l = -1, r = -1;
	}
};

const int MAXMEM = 1e7 + 10;
node tree[MAXMEM];
int topQ = 0;

int clone(int root) {
	tree[topQ] = node();
	tree[topQ].val = tree[root].val;
	tree[topQ].l = tree[root].l;
	tree[topQ].r = tree[root].r;
	topQ++;
	return topQ - 1;
}

int build(int tl, int tr) {
	if (tl == tr - 1) {
		tree[topQ] = node();
		topQ++;
		return topQ - 1;
	}
	int tm = (tl + tr) / 2;
	int l = build(tl, tm);
	int r = build(tm, tr);
	tree[topQ] = node();
	tree[topQ].l = l;
	tree[topQ].r = r;
	topQ++;
	return topQ - 1;
}

int upd(int v, int tl, int tr, int pos, int val) {
	if (tl >= pos + 1 || tr <= pos) return v;
	if (tl == tr - 1) {
		v = clone(v);
		tree[v].val += val;
		return v;
	}
	int tm = (tl + tr) / 2;
	v = clone(v);
	tree[v].l = upd(tree[v].l, tl, tm, pos, val);
	tree[v].r = upd(tree[v].r, tm, tr, pos, val);
	tree[v].val = tree[tree[v].l].val + tree[tree[v].r].val;
	return v;
}

int get(int v, int tl, int tr, int val) {
	if (v == -1) return -1;
	if (tree[v].val < val) return -1; 
	if (tl == tr - 1) return tl;
	int tm = (tl + tr) / 2;
	int ans = get(tree[v].l, tl, tm, val);
	if (ans == -1) {
		ans = get(tree[v].r, tm, tr, val - tree[tree[v].l].val);
	}
	return ans;
}

void wr(int v) {
	if (v == -1) return;
	wr(tree[v].l);
	if (tree[v].l == -1 && tree[v].r == -1) {
		cout << tree[v].val << " ";
	}
	wr(tree[v].r);
} 

const int MAXN = 1e5 + 10;
int n, m;
int a[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}
}

int roots[MAXN];
int base;
int last[MAXN];

void build() {
	base = build(0, n);
	for (int i = 0; i < m; i++)	{
		last[i] = -1;
	}
	roots[n] = base;
	for (int i = n - 1; i >= 0; i--) {
		roots[i] = clone(roots[i + 1]);
		if (last[a[i]] != -1) {
			roots[i] = upd(roots[i], 0, n, last[a[i]], -1);
		}
		last[a[i]] = i;
		roots[i] = upd(roots[i], 0, n, last[a[i]], 1);
	}
}

int get(int l, int k) {
	return get(roots[l], 0, n, k) + 1;
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	int p = 0;
	while (q--) {
		int x, y;
		cin >> x >> y;
		int l = (x + p) % n;
		int k = (y + p) % m + 1;
		p = get(l, k);
		ans.push_back(p);
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