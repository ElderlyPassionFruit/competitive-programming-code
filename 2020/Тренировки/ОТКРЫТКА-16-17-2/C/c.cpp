#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r, cost;
	segment() {};
	segment(int _l) {
		l = _l;
	}
};

bool operator<(const segment & a, const segment & b) {
	return a.l < b.l;
}

int n, k;
vector<segment> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i.l >> i.r >> i.cost;
}

const int INF = 2e9 + 229;
int ans;

struct segment_tree{
	vector<int> tree;
	vector<int> pos;
	vector<multiset<int>> have;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(4 * n, INF);
		have.assign(4 * n, {});
		pos.assign(n, 0);
		build(1, 0, n);
	}

	void upd(int v) {
		v /= 2;
		while (v) {
			tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	void add(int v, int val) {
		v = pos[v];
		tree[v] = val;
		upd(v);
	}
	
	void del(int v) {
		v = pos[v];
		tree[v] = INF;
		upd(v);
	}

	int get(int v, int tl, int tr, int need) {
		if (tree[v] > need) return INF;
		if (tl == tr - 1) return tl;
		int tm = (tl + tr) / 2;
		int ans = get(v * 2, tl, tm, need);
		if (ans == INF)
			ans = get(v * 2 + 1, tm, tr, need);
		return ans;
	}

	int get(int need) {
		return get(1, 0, n, need);
	}
};

vector<int> dp;
segment_tree tree;

struct event{
	int type, pos, val;
	event() {}
	event(int _type, int _pos, int _val) {
		type = _type;
		pos = _pos;
		val = _val;
	}
};

vector<vector<event>> upd;

void relax(int pos) {
	for (auto i : upd[pos]) {
		if (i.type == 1) {
			tree.add(i.pos, i.val);
		}
		else if (i.type == -1) {
			tree.del(i.pos);
		}
	}
	upd[pos].clear();
}

vector<int> order_r;
vector<int> pos_r;

void add_events(int pos) {
	if (dp[pos] == INF) return;
	int first = upper_bound(all(a), segment(dp[pos])) - a.begin();
	if (first == n) return;
	if (first < pos) {
		tree.add(pos_r[pos], a[pos].cost);
	}
	else {
		upd[first].push_back(event(1, pos_r[pos], a[pos].cost));
	}
	int last = upper_bound(all(a), segment(a[pos].r)) - a.begin();
	if (last == n) return;
	upd[last].push_back(event(-1, pos_r[pos], a[pos].cost));
}

bool check(int fans) {
	tree = segment_tree(n);
	dp.assign(n, INF);
	upd.assign(n, {});

	set<int> have;

	for (int i = 0; i < n; i++) {
		relax(i);
		if (a[i].cost <= fans && (a[i].l == 1 || have.count(a[i].l - 1))) {
			dp[i] = a[i].l - 1;
		}	
		
		int pos = tree.get(fans - a[i].cost);
		
		if (pos != INF && a[order_r[pos]].r < a[i].r) {
			chkmin(dp[i], a[order_r[pos]].r);
		}

		if (dp[i] != INF) {
			have.insert(a[i].r);
		}
		add_events(i);		
		relax(i);
	}

	for (int i = 0; i < n; i++) {
		if (a[i].r == k && dp[i] != INF) {
			return true;
		}
	}
	return false;
}

void run() {
	sort(all(a));
	order_r.resize(n);
	iota(all(order_r), 0);
	sort(all(order_r), [&] (int i, int j) {return a[i].r < a[j].r;});
	pos_r.resize(n);
	for (int i = 0; i < n; i++) {
		pos_r[order_r[i]] = i;
	}

	int l = 0, r = INF;
	while (l < r - 1) {
		int mid = l + (r - l) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
}

void write() {
	if (ans == INF) {
		ans = -1;
	}
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