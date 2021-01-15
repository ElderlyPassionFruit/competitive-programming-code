#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct SegmentTree{
	int n;
	vector<int> tree;
	SegmentTree() {}
	SegmentTree(int _n) {
		n = _n;
		tree.assign(n, 0);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos |= pos + 1)
			tree[pos] += val;
	}
	void upd(int l, int r, int x) {
		/*for (int i = l; i <= r; i++) {
			tree[i] += x;
		}*/
		upd(l, x);
		upd(r + 1, -x);
	}

	int get(int pos) {
		int ans = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
			ans += tree[pos];
		}
		return ans;
	}
};

int n,k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
}

vector<int> ans;

void run() {
	for (int it = 0; it < k; it++) {
		SegmentTree tree(n);
		ans.resize(n);
		for (int i = 0; i < n; i++) {
			tree.upd(max(0, i - a[i]), min(n - 1, i + a[i]), 1);
		}
		for (int i = 0; i < n; i++) {
			ans[i] = tree.get(i);
		}
		if (a == ans) break;
		a = ans;
		/*cout << "a = ";
		for (auto i : a) cout << i << " ";
			cout << endl;*/
		//cout << "it = " << it << endl;
	}
}

void write() {
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
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