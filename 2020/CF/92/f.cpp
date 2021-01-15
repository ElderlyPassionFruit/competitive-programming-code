#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct segmentTree{
	int n;
	vector<int> tree;
	segmentTree() {}
	segmentTree(int _n) {
		n = _n;
		tree.assign(n, 0);
	}
	void upd(int l, int r, int x) {
		for (int i = l; i <= r; i++) {
			tree[i] += x;
		}
	}
	int get() {
		return *max_element(all(tree));
	}
};

struct seg{
	int l, r;
};

const int N = 4e5 + 10;

int n;
vector<seg> a[2];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		seg x;
		cin >> x.l >> x.r;
		int t;
		cin >> t;
		a[t - 1].push_back(x);
	}
}

vector<int> L[N][2];
int sz;
segmentTree tree;

void buildCoord() {
	vector<int> have;
	for (int it = 0; it < 2; it++) {
		for (auto [l, r] : a[it]) {
			have.push_back(l);
			have.push_back(r);
		}
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (int it = 0; it < 2; it++) {
		for (auto &[l, r] : a[it]) {
			l = lower_bound(all(have), l) - have.begin();
			r = lower_bound(all(have), r) - have.begin();
			L[r][it].push_back(l);
		}
	}
	sz = have.size();
}

int ans = 0;

void solve() {
	tree = segmentTree(sz);
	for (int r = 0; r < sz; r++) {
		if (r > 0) {
			for (auto l : L[r - 1][0]) {
				tree.upd(0, l - 1, 1);
			}
		}
	}
}

void run() {
	buildCoord();
	solve();
	for (int i = 0; i < sz; i++) {
		swap(L[i][0], L[i][1]);
	}
	solve();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}