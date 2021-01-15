#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r;
	segment() {}
	segment(int a, int b) {
		l = a, r = b;
	}
};

int n;
vector<segment> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.l >> i.r, i.l *= 2, i.r *= 2;
}

const int INF = -1e9 - 10;

struct node{
	int l, r, ans;
	node() {
		ans = INF;
		l = 0, r = 0, ans = 0;
	}	
};

node merge(node a, node b) {
	if (a.ans == INF) return b;
	if (b.ans == INF) return a; 
	node ans;
	ans.l = a.l;
	ans.r = b.r;
	ans.mod = 0;
	ans.ans = a.ans + b.ans;
	if (a.r > 0 && b.l > 0) 
		ans.ans--;
	return ans;
}
struct segment_tree{

	vector<node> tree;
	vector<int> mod;
	int n;
	segment_tree() {}
	segment_tree(int sz) {
		n = sz;
		tree.assign(4 * n, node());
		mod.assign(4 * n, 0);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
	}

	node get_val(int )

	void upd(int v, int tl, int tr, int l, int r, int val) {

	}

	void upd(int l, int r, int val) {
		for (int i = l; i <= r; i++) {
			tree[i].l += val;
			tree[i].r += val;
			if (tree[i].l > 0) {
				tree[i].ans = 1;
			} 
			else {
				tree[i].ans = 0;
			}
		}
	}

	int get() {
		node ans;
		for (int i = 0; i < n; i++) {
			ans = merge(ans, tree[i]);
		}
		return ans.ans;
	}
};


void build() {
	vector<int> have;
	for (auto i : a) {
		have.push_back(i.l);
		have.push_back(i.l - 1);
		have.push_back(i.l + 1);

		have.push_back(i.r);
		have.push_back(i.r - 1);
		have.push_back(i.r + 1);
	} 
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i.l = lower_bound(all(have), i.l) - have.begin();
		i.r = lower_bound(all(have), i.r) - have.begin();
	}
}

int ans;

void run() {
	build();
	ans = 0;
	for (int i = 0; i < n; i++) {
		tree.upd(a[i].l, a[i].r, 1);
	}
	
	for (int i = 0; i < n; i++) {
		tree.upd(a[i].l, a[i].r, 1);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}