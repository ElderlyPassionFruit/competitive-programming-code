#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

ll query(int pos1, int pos2) {
	cout << "swap " << pos1 << " " << pos2 << endl;
	ll ans;
	cin >> ans;
	return ans;
}

int n;
ll have;
vector<int> a;
	 
void out_ans(vector<int> ans) {
	cout << "answer ";
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << endl;
	exit(0);
}

struct segment_tree{
	vector<int> tree;
	vector<int> pos;
	int n;
	segment_tree() {}
	
	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			tree[v] = 1;
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(4 * n, 0);
		pos.assign(n, 0);
		build(1, 0, n);
	}

	int get_kth(int v, int tl, int tr, int l, int r, int k) {
		if (tree[v] < k) return -1;
		if (tl >= r || tr <= l) return -1;
		if (tl == tr - 1) {
			return tl;
		}
		int tm = (tl + tr) / 2;
		int ans = get_kth(v * 2 + 1, tm, tr, l, r, k);
		if (ans == -1) {
			ans = get_kth(v * 2, tl, tm, l, r, k - tree[v * 2 + 1]);
		}
		return ans;
	}

	int get_val(int need) {
		return get_kth(1, 0, n, 0, n, need + 1);
		int ans = 0;
		need++;
		for (int i = n - 1; i >= 0; i--) {
			ans += tree[i];
			if (ans == need) {
				return i;
			} 
		}
		assert(false);
	}
	
	void set_val(int v) {
		v = pos[v];
		tree[v] = 0;
		v /= 2;
		while (v) {
			tree[v] = tree[v * 2] + tree[v * 2 + 1];
			v /= 2;
		}
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> have;

	a.resize(n);
	iota(all(a), 1);
	int pos_max = 1;
	vector<pair<int, int>> op;

	for (int i = 2; i <= n; i++) {
		ll fans = query(pos_max, i);
		op.push_back({pos_max - 1, i - 1});
		if (fans < have) {
			pos_max = i;
		}
		have = fans;
	}
	if (pos_max != 1) {
		op.push_back({0, pos_max - 1});
		query(1, pos_max);
	}

	vector<int> inv;
	inv.push_back(0);
	for (int i = 2; i <= n; i++) {
		ll a = query(1, i);
		ll b = query(1, i);
		inv.push_back((b - a + 1) / 2);
		assert((b - a + 1) % 2 == 0);
	}

	vector<int> ans(n);
	segment_tree tree(n);
	ans[0] = n - 1;
		
	for (int i = n - 1; i >= 1; i--) {
		ans[i] = tree.get_val(inv[i]);
		tree.set_val(ans[i]);
	}

	reverse(all(op));
	for (auto i : op) {
		swap(ans[i.first], ans[i.second]);
	}

	out_ans(ans);
	return 0;
}