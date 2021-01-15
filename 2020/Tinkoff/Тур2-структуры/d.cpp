#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct merge_sort_tree{
	vector<vector<int> > tree;
	int n;

	merge_sort_tree() {
		n = 0;
		tree = {};
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = {a[tl]};
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v].resize(tree[v * 2].size() + tree[v * 2 + 1].size());
		merge(tree[v * 2].begin(), tree[v * 2].end(), tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(), tree[v].begin());
	}

	merge_sort_tree(vector<int> a) {
		n = a.size();
		tree.resize(4 * n);
		build(1, 0, n, a);
	}

	int get(int v, int x, int y) {
		int s = lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin();
		int f = (--upper_bound(tree[v].begin(), tree[v].end(), y)) - tree[v].begin();
		return f - s + 1;
	}

	int get(int v, int tl, int tr, int l, int r, int x, int y) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return get(v, x, y);
		int tm = (tl + tr) / 2;
		return get(v * 2, tl, tm, l, r, x, y) + get(v * 2 + 1, tm, tr, l, r, x, y);
	}

	int get(int l, int r, int x, int y) {
		return get(1, 0, n, l, r + 1, x, y);
	}
};

int n, q;
vector<int> a;
merge_sort_tree tree;

void read() {
	cin >> n >> q;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	tree = merge_sort_tree(a);
}

vector<int> ans;

void run() {
	for (int test = 0; test < q; test++) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		l--;
		r--;
		int fans = tree.get(l, r, x, y);
		ans.push_back(fans);
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