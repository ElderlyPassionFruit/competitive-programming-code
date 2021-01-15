#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct segmentTree{
	int n;
	vector<int> tree;
	vector<int> pos;
	segmentTree() {}

	void build(int v, int tl, int tr) {
		if (tl >= tr) return;
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}
	segmentTree(int _n) {
		n = _n;
		tree.assign(4 * n, 0);
		pos.assign(n, 0);
		build(1, 0, n);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
		int ans = 0;
		for (int i = l; i <= r; i++) {
			ans = max(ans, tree[i]);
		}
		return ans;
	}

	void upd(int v, int val) {
		v = pos[v];
		tree[v] = max(tree[v], val);
		v /= 2;
		while (v) {
			tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}
};

int n;
vector<int> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
	segmentTree dp(n);
	for (int i = 0; i < n; i++) {
		int have = dp.get(0, a[i]);
		dp.upd(a[i], have + 1);
	}
	cout << dp.get(0, n - 1) << endl;
	return 0;
}