#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

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

int n, q;

void read() {
	cin >> n >> q;
}

void run() {
	vector<int> a(n, 0);
	fenvik tree(n);
	while (q--) {
		char t;
		int x, y;
		cin >> t >> x >> y;
		if (t == 'A') {
			tree.upd(x - 1, -a[x - 1]);
			a[x - 1] = y;
			tree.upd(x - 1, a[x - 1]);
		} else {
			cout << tree.get(x - 1, y - 1) << "\n";
		}
	}
}

void write() {

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