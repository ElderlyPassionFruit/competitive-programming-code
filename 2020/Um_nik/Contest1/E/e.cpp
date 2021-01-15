#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct segmentTree{
	int n;
	vector<int> tree;
	vector<int> mod;
	segmentTree() {}
	segmentTree(int _n) {
		n = _n;
		tree.assign(4 * n, 0);
		mod.assign(4 * n, 0);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		tree[v] += mod[v];
		mod[v] = 0;
	}

	int getVal(int v) {
		return tree[v] + mod[v];
	}

	void upd(int v, int tl, int tr, int l, int r, int x) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			mod[v] += x;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, x);
		upd(v * 2 + 1, tm, tr, l, r, x);
		tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
	}

	void upd(int l, int r, int x) {
		upd(1, 0, n, l, r + 1, x);
		//return;
		//for (int i = l; i <= r; i++) {
		//	tree[i] += x;
		//}
	}

	int getMin() {
		return getVal(1);
		//return *min_element(all(tree));
	}
};

int n, len, h;
vector<int> a, b;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> len >> h;
	b.resize(len);
	for (auto &i : b) {
		cin >> i;
		i = h - i;
	}
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	auto have = b;
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	segmentTree tree(have.size());
	for (auto i : b) {
		int pos = lower_bound(all(have), i) - have.begin();
		tree.upd(0, pos, -1);
	}
	int ans = 0;
	for (int i = 0; i < len; i++) {
		int pos = --upper_bound(all(have), a[i]) - have.begin();
		tree.upd(0, pos, 1);
	}
	ans += tree.getMin() >= 0;
	for (int i = len; i < n; i++) {
		int pos;
		pos = --upper_bound(all(have), a[i]) - have.begin();
		tree.upd(0, pos, 1);
		pos = --upper_bound(all(have), a[i - len]) - have.begin();
		tree.upd(0, pos, -1);
		ans += tree.getMin() >= 0;
	}
	cout << ans << endl;
	return 0;
}