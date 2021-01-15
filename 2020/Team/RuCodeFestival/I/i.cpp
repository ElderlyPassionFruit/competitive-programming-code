#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}

	fenvik(int _sz) {
		n = _sz;
		tree.assign(n, 0);
	}

	void upd(int pos, int val) {
		for (; pos < n; pos |= pos + 1)
		tree[pos] += val;
	}

	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			ans += tree[r];
		}
		return ans;
	}
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
	fenvik tree(n);
	int ans = 0;
	int mx = 0;
	for (int i = 0; i < n; i++) {
		mx = max(mx, a[i]);
		ans = max(ans, mx - tree.get(mx));
		//cout << mx << " " << tree.get(a[i]) << endl;
		tree.upd(a[i], 1);
	}
	if (ans * 2 > n) {
		cout << -1 << endl;
	} else {
		cout.precision(20);
		cout.setf(ios::fixed);
		cout << (ld) ans / n << endl;
	}
	return 0;
}