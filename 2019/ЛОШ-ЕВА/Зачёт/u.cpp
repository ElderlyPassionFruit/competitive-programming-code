#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, q;

void read() {
	cin >> n >> m >> q;
}

const int INF = 1e9;

struct node{
	int max, min, pos_min, mod;
	node() {
		max = min = mod = pos_min = 0;
	}
	node(int pos) {
		max = min = mod = 0;
		pos_min = pos;
	}
};

node merge(const node & a, const node & b) {
	node ans;
	ans.max = max(a.max, b.max);
	ans.min = min(a.min, b.min);
	ans.mod = 0;
	ans.pos_min = b.pos_min;
	if (ans.min == a.min)
		ans.pos_min = a.pos_min;
	return ans;
}

struct segment_tree{
	vector<node> tree;
	int n;

	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			tree[v] = node(tl);
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(int sz) {
		n = sz;
		tree.resize(n * 4);
		build(1, 0, n);
	}

	void push(int v) {
		tree[v * 2].mod += tree[v].mod;
		tree[v * 2 + 1].mod += tree[v].mod;
		tree[v].mod = 0;
	}

	node get_val(int v) {
		node ans = tree[v];
		ans.min += ans.mod;
		ans.max += ans.mod;
		ans.mod = 0;
		return ans;
	}

	int get_max(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return -INF;
		if (tl >= l && tr <= r) return get_val(v).max;
		push(v);
		int tm = (tl + tr) / 2;
		int ans = max(get_max(v * 2, tl, tm, l, r), get_max(v * 2 + 1, tm, tr, l, r));
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	int get_max(int l, int r) {
		return get_max(1, 0, n, l, r + 1);
	}

	int get_l(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return -INF;
		if (get_val(v).min > val) return -INF;
		if (tl == tr - 1) return tl;
		push(v);
		int tm = (tl + tr) / 2;
		int ans = get_l(v * 2 + 1, tm, tr, l, r, val);
		if (ans == -INF)
			ans = get_l(v * 2, tl, tm, l, r, val);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	int get_l(int pos, int val) {
		return get_l(1, 0, n, 0, pos + 1, val);
	}

	int get_r(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return INF;
		if (get_val(v).min > val) return INF;
		if (tl == tr - 1) return tl;
		push(v);
		int tm = (tl + tr) / 2;
		int ans = get_r(v * 2, tl, tm, l, r, val);
		if (ans == INF)
			ans = get_r(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	int get_r(int pos, int val) {
		return get_r(1, 0, n, pos, n, val);
	}

	int get_pos(int pos) {
		return get_max(1, 0, n, pos, pos + 1);
	}

	void clear(int v, int tl, int tr, int pos) {
		if (tl >= pos + 1 || tr <= pos) return;
		if (tl == tr - 1) {
			tree[v] = 0;
			tree[v].mod = 0;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		clear(v * 2, tl, tm, pos);
		clear(v * 2 + 1, tm, tr, pos);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}

	void clear(int pos) {
		clear(1, 0, n, pos);
	}

	void add() {
		tree[1].mod++;
	}
};

segment_tree X, Y;

void build() {
	X = segment_tree(n);
	Y = segment_tree(m);
}

void add() {
	X.add();
	Y.add();
}

void clear_x(int x) {
	X.clear(x);
}

void clear_y(int y) {
	Y.clear(y);
}

int get(int x1, int y1, int x2, int y2, int k) {
	int X1 = X.get_pos(x1);
	int X2 = X.get_pos(x2);
	int Y1 = Y.get_pos(y1);
	int Y2 = Y.get_pos(y2);

	if ((X1 <= k && Y2 <= k) || (Y1 <= k && X2 <= k))
		return abs(x1 - x2) + abs(y1 - y2);

	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);

	int max_x = X.get_max(x1, x2);
	int max_y = Y.get_max(y1, y2);

	if (min(max_x, max_y) <= k)
		return abs(x1 - x2) + abs(y1 - y2);

	int ans = INF;
	if (Y1 <= k && Y2 <= k) {
		int pos = X.get_r(x1, k);
		chkmin(ans, abs(x1 - pos) + abs(x2 - pos) + abs(y1 - y2));
		pos = X.get_l(x2, k);
		chkmin(ans, abs(x1 - pos) + abs(x2 - pos) + abs(y1 - y2));
	}
	
	if (X1 <= k && X2 <= k) {
		int pos = Y.get_r(y1, k);
		chkmin(ans, abs(y1 - pos) + abs(y2 - pos) + abs(x1 - x2));
		pos = Y.get_l(y2, k);
		chkmin(ans, abs(y1 - pos) + abs(y2 - pos) + abs(x1 - x2));
	}

	if (ans > INF / 2)
		return -1;
	return ans;
}

vector<int> ans;

void run() {
	build();
	for (int test = 0; test < q; test++) {
		add();
		int type;
		cin >> type;
		if (type == 1) {
			int x;
			cin >> x;
			x--;
			clear_x(x);
		}
		else if (type == 2) {
			int y;
			cin >> y;
			y--;
			clear_y(y);
		}
		else {
			int x1, y1, x2, y2, k;
			cin >> x1 >> y1 >> x2 >> y2 >> k;
			x1--;
			y1--;
			x2--;
			y2--;
			ans.push_back(get(x1, y1, x2, y2, k));
		}
	}	
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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