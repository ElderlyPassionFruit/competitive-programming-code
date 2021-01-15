#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment_tree{
	vector<vector<int>> tree;
	int n;
	segment_tree() {
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

	segment_tree(vector<int> a) {
		n = a.size();
		tree.resize(n * 4);
		build(1, 0, n, a);
	}

	int get_ans(int v, int r) {
		int pos = lower_bound(tree[v].begin(), tree[v].end(), r) - tree[v].begin();
		return tree[v].size() - pos;
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return get_ans(v, r);
		int tm = (tl + tr) / 2;
		return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
		/*int ans = 0;
		for (int i = l; i <= r; i++) {
			ans += tree[i] > r;
		}
		return ans;*/
	}
};

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}


segment_tree tree;
const int MAXN = 1e5 + 10, INF = 1e9 + 10;
vector<int> ind[MAXN];
int pos[MAXN];

void build() {
	for (int i = 0; i < n; i++) {
		pos[i] = ind[a[i]].size();
		ind[a[i]].push_back(i);
	}

	vector<int> fbuild(n);
	for (int i = 0; i < n; i++) {
		if (pos[i] + k >= ind[a[i]].size())
			fbuild[i] = INF;
		else
			fbuild[i] = ind[a[i]][pos[i] + k];
	}
	tree = segment_tree(fbuild);
}

vector<int> ans;

void run() {
	build();
	int last = 0;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l = (l + last) % n + 1;
		r = (r + last) % n + 1;
		if (l > r)
			swap(l, r);
		l--;
		r--;
		last = tree.get(l, r);
		ans.push_back(last);
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