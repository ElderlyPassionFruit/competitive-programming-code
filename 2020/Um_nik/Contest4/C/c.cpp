#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct event{
	int l, ind;
	event() {}
	event(int _l, int _ind) {
		l = _l, ind = _ind;
	}
};

struct fenwick{
	vector<int> tree;
	int n;
	fenwick() {}
	fenwick(int _n) {
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
		for (; pos < n; pos |= pos + 1) {
			tree[pos] += val;
		}
	}
};

const int INF = 1e9 + 228 + 1337;

struct segmentTree{
	vector<int> tree;
	vector<int> pos;
	int n;
	segmentTree() {}
	void build(int v, int tl, int tr) {
		if (tl >= tr) return;
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}
	segmentTree(int _n) {
		n = _n;
		tree.assign(4 * n, INF);
		pos.resize(n);
		build(1, 0, n);
	}
	void upd(int v, int val) {
		v = pos[v];
		tree[v] = val;
		v /= 2;
		while (v) {
			tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return INF;
		if (tl >= l && tr <= r) return tree[v];
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

int n;
vector<int> a;

void solve() {
	int l, r;
	cin >> l >> r;
	l--;
	r--;
	map<int, int> d;
	map<int, int> last;
	map<int, bool> good;
	for (int i = l; i <= r; i++) {
		if (!last.count(a[i])) {
			good[a[i]] = true;
		} else if (!d.count(a[i])) {
			d[a[i]] = i - last[a[i]];
		} else {
			if (i - last[a[i]] != d[a[i]]) {
				good[a[i]] = false;
			}
		}
		last[a[i]] = i;
	}
	bool ok = false;
	for (auto i : good) {
		ok |= i.second;
	}
	int ans = good.size();
	if (!ok) ans++;
	cout << ans << "\n";
}

void Unique(vector<int> & a) {
	auto have = a;
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i = lower_bound(all(have), i) - have.begin();
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	Unique(a);
	int q;
	cin >> q;
	vector<vector<event>> fq(n);
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		fq[r].push_back({l, i});
	}

	vector<int> ans(q);
	fenwick diff(n);
	segmentTree minL(n);
	vector<int> last(n, -1);
	vector<int> d(n, -1);

	for (int i = 0; i < n; i++) {
		if (last[a[i]] != -1) {
			diff.upd(last[a[i]], -1);		
			diff.upd(i, 1);
			int myL = minL.get(last[a[i]], last[a[i]]);
			minL.upd(last[a[i]], INF);
			if (d[a[i]] != -1) {
				if (i - last[a[i]] == d[a[i]]) {
					minL.upd(i, myL);
				} else {
					minL.upd(i, last[a[i]] - d[a[i]] + 1);
				}
				d[a[i]] = i - last[a[i]];
			} else {
				d[a[i]] = i - last[a[i]];
				minL.upd(i, 0);
			}
			last[a[i]] = i;
		} else {
			diff.upd(i, 1);
			minL.upd(i, 0);
			last[a[i]] = i;
		}
		for (auto [l, ind] : fq[i]) {
			int cntDiff = diff.get(l, i);
			int myL = minL.get(l, i);
			if (myL <= l) {
				ans[ind] = cntDiff;
			} else {
				ans[ind] = cntDiff + 1;
			}
		}
	}

	for (auto i : ans) {
		cout << i << "\n";
	}
	return 0;
}