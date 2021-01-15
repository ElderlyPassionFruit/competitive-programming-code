#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int _n) {
		n = _n;
		tree.assign(n, 0);
	}
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			ans += tree[r];
		}
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

int n;
fenvik a;

void solve() {
	int x;
	cin >> x;
	x--;
	int ans = min(a.get(0, x - 1), a.get(x + 1, n - 1));
	a.upd(x, 1);
	cout << ans << " ";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a = fenvik(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.upd(i, x);
	} 
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
	cout << endl;
	return 0;
}