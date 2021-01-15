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

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i, i--;
}

ll ans;
vector<vector<int>> have;

void run() {
	have.resize(n);
	for (int i = 1; i < n; i++) {
		have[min(a[i], i - 1)].push_back(i);
	}
	/*cout << "have = " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j : have[i]) {
			cout << j << " ";
		}
		cout << endl;
	}*/
	fenvik tree(n + 1);
	ans = 0;
	for (int i = 0; i < n; i++) {
		tree.upd(min(a[i], n), 1);
		for (auto j : have[i]) {
			ans += tree.get(j, n);
		}
	}
}

void write() {
	cout << ans << endl;
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