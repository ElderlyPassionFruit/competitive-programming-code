#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int INF = 1e9;
const int MAXLOG = 18;

struct segment_tree{
	vector<int> tree;
	vector<int> mod;
	int n;
	segment_tree() {
		n = 0;
		tree = {};
	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(n * 4, 0);
		mod.assign(n * 4, 0);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		tree[v] += mod[v];
		mod[v] = 0;
	}

	int get_val(int v) {
		return tree[v] + mod[v];
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return;
		if (tl >= l && tr <= r) {
			mod[v] += val;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = max(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int pos, int val) {
		upd(1, 0, n, 0, pos + 1, val);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return -INF;
		if (tl >= l && tr <= r)
			return get_val(v);
		push(v);
		int tm = (tl + tr) / 2;
		auto ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		tree[v] = max(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}

	int get() {
		if (get(0, n - 1) <= 0)
			return -1;
		int l = 0, r = n;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (get(mid, n - 1) > 0)
				l = mid;
			else
				r = mid;
		} 
		return l;
	}
}; 

int m;
segment_tree tree;
void read() {
	cin >> m;
	tree = segment_tree(m);
}

vector<int> num;
vector<int> ans;

void run() {
	num.assign(m, 0);
	for (int test = 0; test < m; test++) {
		int p, t;
		cin >> p >> t;
		p--;
		if (t == 0) {
			tree.upd(p, -1);
		}
		if (t == 1) {
			int x;
			cin >> x;
			tree.upd(p, 1);
			num[p] = x;
		}
		int pos = tree.get();
		if (pos == -1)
			ans.push_back(-1);
		else
			ans.push_back(num[pos]);
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