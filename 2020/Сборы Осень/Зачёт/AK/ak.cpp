#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int min, sum, mod;
	node() {
		min = 0, sum = 1, mod = 0;
	}
	node(int a, int b) {
		min = a, sum = b, mod = 0;
	}
};

node merge(const node & a, const node & b) {
	node ans;
	if (a.min < b.min)
		ans = a;
	else if (a.min > b.min)
		ans = b;
	else
		ans = node(a.min, a.sum + b.sum);
	return ans;
}

struct segment_tree{
	vector<node> tree;
	int n;
	segment_tree() {}
	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = node(0, a[tl]);
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}
	segment_tree(int sz) {
		n = sz;
		tree.resize(4 * n);
	}
	segment_tree(vector<int> a) {
		n = a.size();
		tree.resize(n * 4);
		build(1, 0, n, a);
	}

	void push(int v) {
		tree[v * 2].mod += tree[v].mod;
		tree[v * 2 + 1].mod += tree[v].mod;
		tree[v].mod = 0;
	}

	node get_val(int v) {
		return node(tree[v].min + tree[v].mod, tree[v].sum);
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return node(1e9, 0);
		if (tl >= l && tr <= r) return get_val(v);
		int tm = (tl + tr) / 2;
		push(v);
		node ans = merge(
			get(v * 2, tl, tm, l, r),
			get(v * 2 + 1, tm, tr, l, r)
		);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	node get(int l, int r) {
		return get(1, 0, n, l, r);
		//node ans(1e9, 0);
		//for (int i = l; i < r; i++) {
		//	ans = merge(ans, tree[i]);
		//}
		//return ans;
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			tree[v].mod += val;
			return;
		}
		int tm = (tl + tr) / 2;
		push(v);
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r, val);
		//for (int i = l; i < r; i++) {
		//	tree[i].min += val;
		//}
	}
};

struct event{
	int x, y1, y2, type;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y1 = b, y2 = c, type = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

int n;
vector<event> a;

void read() {
	cin >> n;
	if (n == 0) {
		cout << 0 << endl;
		exit(0);
	}
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a.push_back({x1, y1, y2, 1});
		a.push_back({x2, y1, y2, -1});
	}
}

segment_tree tree;

int full;

void build() {
	vector<int> have;
	for (auto i : a) {
		have.push_back(i.y1);
		have.push_back(i.y2);
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i.y1 = lower_bound(all(have), i.y1) - have.begin();
		i.y2 = lower_bound(all(have), i.y2) - have.begin();
	}
	full = have.back() - have[0];
	for (int i = have.size() - 1; i >= 1; i--) {
		have[i] = have[i] - have[i - 1];
	}
	have.erase(have.begin());
	tree = segment_tree(have);
}

int ans;

void run() {
	build();
	sort(all(a));
	int last = a[0].x;
	int l = 0, r = 0;
	while (l < a.size()) {
		auto fans = tree.get(0, tree.n);
		int len = full;
		if (fans.min == 0) {
			len -= fans.sum;
		}
		ans += len * (a[l].x - last);
		//cout << "x = " << a[l].x << " fans = " << len * (a[l].x - last) << endl;
		//cout << "fans = " << fans.min << " " << fans.sum << endl;
		last = a[l].x;
		while (r < a.size() && a[l].x == a[r].x) {
			tree.upd(a[r].y1, a[r].y2, a[r].type);
			r++;
		}
		l = r;
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