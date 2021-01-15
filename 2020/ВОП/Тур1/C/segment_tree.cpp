#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct segment_tree{
	vector<int> tree;
	vector<int> a;
	int n;
	segment_tree() {}
	segment_tree(const vector<int> & _a) {
		a = _a;
		n = a.size();
		tree.assign(n, 0);
	}

	void upd(int l, int r, int val) {
		for (int i = l; i <= r; i++) {
			tree[i] += val;
		}
	}

	int get() {
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (!tree[i]) {
				ans += a[i];
			}
		}
		return ans;
	}
};

struct event{
	int x, l, r, type;
	event() {}
	event(int _x, int _l, int _r, int _type) {
		x = _x, l = _l, r = _r, type = _type;
	}
};

bool operator<(const event & a, const event & b) {
	return a.x < b.x;
}

int k, c, t;
vector<event> a;

void read() {
	cin >> k >> c >> t;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		int nx = x + y;
		int ny = x - y;
		a.push_back({nx - t, ny - t, ny + t, 1});
		a.push_back({nx + t + 1, ny - t, ny + t, -1});
	}
}

segment_tree tree;
int full;

void make() {
	vector<int> have;
	for (auto i : a) {
		have.push_back(i.l);
		have.push_back(i.r);
	}
	have.push_back(0);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i.l = lower_bound(all(have), i.l) - have.begin();
		i.r = lower_bound(all(have), i.r) - have.begin();
	}
	vector<int> d;
	for (int i = 1; i < (int)have.size(); i++) {
		d.push_back(have[i] - have[i - 1]);
	}
	tree = segment_tree(d);
	full = have.back() - have[0];
}

ll ans;

void run() {
	make();
	sort(all(a));
	for (int i = 0; i < (int)a.size(); i++) {
		int pos = i;
		while (pos < (int)a.size() && a[pos].x == a[i].x) {
			tree.upd(a[pos].l, a[pos].r, a[pos].type);
			pos++;
		}		
		int have = tree.get();
		if (i != 0) {
			ans += (full - have) * (a[i].x - a[i - 1].x);
		}
		i = pos - 1;
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}