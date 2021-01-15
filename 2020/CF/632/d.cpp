#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int _sz) {
		n = _sz;
		tree.assign(n, 0);
	}
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos |= pos + 1)
			tree[pos] += val;
	}
};

fenvik tree[40];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < 40; i++)
		tree[i] = fenvik(n);
	vector<int> a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		a.push_back(x);
		tree[x].upd(i, 1);
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			int ans = 0;
			for (int i = 0; i < 40; i++) {
				ans += tree[i].get(l, r) > 0;
			}
			cout << ans << "\n";
		} else {
			int pos, val;
			cin >> pos >> val;
			pos--;
			tree[a[pos]].upd(pos, -1);
			a[pos] = val - 1;
			tree[a[pos]].upd(pos, 1);
		}
	}
	return 0;
}