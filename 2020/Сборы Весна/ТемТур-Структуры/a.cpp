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

int n, m;
vector<int> a;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i, i--;

}

struct event{
	int l, r, ind, type;
	event() {}
	event(int _l, int _r, int _ind, int _type) {
		l = _l, r = _r, ind = _ind, type = _type;
	}
};

vector<vector<event>> have;

vector<int> ans;

void run() {
	have.resize(n);
	ans.resize(m);
	for (int i = 0; i < m; i++) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		l--;
		r--;
		x--;
		y--;
		if (l > 0)
			have[l - 1].push_back({x, y, i, -1});
		have[r].push_back({x, y, i, 1});
	}
	fenvik tree(n);
	for (int i = 0; i < n; i++) {
		tree.upd(a[i], 1);
		for (auto j : have[i]) {
			ans[j.ind] += j.type * tree.get(j.l, j.r);
		}
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
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