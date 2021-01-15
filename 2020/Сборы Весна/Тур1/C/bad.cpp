#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

struct segment{
	int l, r, t, c;
	segment() {}
	segment(int _l, int _r, int _t, int _c) {
		l = _l, r = _r, t = _t, c = _c;
	}
};

bool operator<(const segment & a, const segment & b) {
	return a.r < b.r;
}

int n, m;
vector<segment> have;

void read() {
	cin >> n >> m;
	have.resize(m);
	for (auto &i : have) {
		cin >> i.t >> i.l >> i.r >> i.c;
	}
}

vector<segment> make(int t) {
	vector<segment> ans;
	for (auto i : have) {
		if (i.t > t) continue;
		i.l += t - i.t;
		i.r -= t - i.t;
		if (i.l <= i.r) {
			ans.push_back(i);
		}
	}
	return ans;
}

const int INF = 1e18;

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {}
	segment_tree(int _n) {
		n = _n;
		tree.assign(n, INF);
	}

	void upd(int pos, int val) {
		chkmin(tree[pos], val);
	}

	int get(int l, int r) {
		int ans = INF;
		for (int i = l; i <= r; i++) {
			chkmin(ans, tree[i]);
		}
		return ans;
	}
};

int calc(int t) {
	vector<segment> have = make(t);
	/*cout << "have = " << endl;
	for (auto i : have) {
		cout << i.t << " " << i.l << " " << i.r << " " << i.c << endl;
	}*/
	vector<int> c;
	c.push_back(0);
	for (auto i : have)
		c.push_back(i.l), c.push_back(i.r);
	c.push_back(n);
	sort(all(c));
	c.resize(unique(all(c)) - c.begin());
	segment_tree dp(c.size());
	dp.upd(0, 0);
	sort(all(have));
	for (auto i : have) {
		int l = lower_bound(all(c), i.l) - c.begin();
		if (c[l - 1] == i.l - 1) l--;
		int r = lower_bound(all(c), i.r) - c.begin();
		int fupd = dp.get(l, r);
		if (fupd == INF) continue;
		dp.upd(r, fupd + i.c);
	}
	return dp.get(c.size() - 1, c.size() - 1);
}

int ans;

void run() {
	ans = INF;
	vector<int> t;
	for (auto i : have) t.push_back(i.t);
	sort(all(t));
	t.resize(unique(all(t)) - t.begin());
	for (auto i : t) {
		chkmin(ans, calc(i));
	}
	if (ans == INF) ans = -1;
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