#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct query{
	int pos, ind;
	query() {}
	query(int a, int b) {
		pos = a, ind = b;
	}
};

const int MAXN = 1e6 + 10;

int n, q, k;
vector<int> a;
vector<query> rq[MAXN];
vector<query> lq[MAXN];
void read() {
	cin >> n >> q >> k;
	a.resize(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		rq[r].push_back({l, i});
		lq[l].push_back({r, i});
	}
}

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {}
	segment_tree(vector<int> a) {
		tree = a;
		n = a.size();
	}
	int get_L(int r, int L, int R) {
		for (int i = r; i >= 0; i--)
			if (L <= tree[i] && tree[i] <= R)
				return i;
		return -1;
	}
	int get_R(int l, int L, int R) {
		for (int i = l; i < n; i++)
			if (L <= tree[i] && tree[i] <= R)
				return i;
		return -1;
	}
};

int l[MAXN][2], r[MAXN][2];

void build() {
	segment_tree tree(a);
	for (int i = 0; i < n; i++) {
		l[i][0] = tree.get_L(i - 1, a[i] - k, a[i]);
		l[i][1] = tree.get_R(i + 1, a[i] - k, a[i]);
		r[i][0] = tree.get_L(i - 1, a[i], a[i] + k);
		r[i][1] = tree.get_R(i + 1, a[i], a[i] + k);
	}

	cout << "l = " << endl;
	for (int i = 0; i < n; i++) {
		cout << l[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << l[i][1] << " ";
	}
	cout << endl;
}

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int sz) {
		n = sz;
		tree.assign(n, 0);
	}
	int get(int l, int r) {
		int ans = 0;
		for (int i = l; i <= r; i++)
			ans += tree[i];
		return ans;
	}
	void upd(int pos, int val) {
		tree[pos] += val; 
	}
};

int ans[MAXN];

void solve_L() {
	fenvik tree(n);
	vector<vector<int>> add(n);
	for (int i = n - 1; i >= 0; i--) {
		if (l[i][0] != -1)
			add[l[i][0]].push_back(i);
		if (l[i][1] != -1)
			tree.upd(l[i][1], 1);
		for (auto j : add[i]) {
			tree.upd(j, 1);
			if (l[j][1] != -1)
				tree.upd(l[j][1], -1);
		}
		for (auto j : lq[i])
			ans[j.ind] += tree.get(i, j.pos);
	}
}

void solve_R() {
	fenvik tree(n);
	vector<vector<int>> add(n);
	for (int i = 0; i < n; i++) {
		if (r[i][1] != -1)
			add[r[i][1]].push_back(i);
		if (r[i][0] != -1)
			tree.upd(r[i][0], 1);
		for (auto j : add[i]) {
			tree.upd(j, 1);
			if (r[j][0] != -1)
				tree.upd(r[j][0], -1);
		}
		for (auto j : rq[i])
			ans[j.ind] += tree.get(j.pos, i);
	}
}

struct event{
	int pos_add, pos_del;
	event() {}
	event(int a, int b) {
		pos_add = a, pos_del = b;
	}
};

void solve_LR() {
	fenvik tree(n);
	vector<vector<event>> add(n);
	for (int i = 0; i < n; i++) {
		bool l0 = l[i][0] != -1;
		bool l1 = l[i][1] != -1;
		bool r0 = r[i][0] != -1;
		bool r1 = r[i][1] != -1;

		if ((l0 || l1) && (r0 || r1)) {
			if (l0 && r0) {
				tree.upd(min(l[i][0], r[i][0]), -1);
				if (l1 && r1) {
					if (l[i][1] < r[i][1]) {
						add[l[i][1]].push_back({r[i][0], min(l[i][0], r[i][0])});
						add[r[i][1]].push_back({i, r[i][0]});
					}
					else {
						add[r[i][1]].push_back({l[i][0], min(l[i][0], r[i][0])});
						add[l[i][1]].push_back({i, l[i][0]});
					}
				}
				else if (l1) {
					add[l[i][1]].push_back({r[i][0], min(l[i][0], r[i][0])});
				}
				else if (r1) {
					add[r[i][1]].push_back({l[i][0], min(l[i][0], r[i][0])});	
				}
			}
			else {
				if (l0) {
					if (r1) { 
						if (l[i][1] < r[i][1]) {
							add[r[i][1]].push_back({i, -1});
						}
						else {
							add[r[i][1]].push_back({l[i][0], -1});
							if (l1)
								add[l[i][1]].push_back({i, l[i][0]});
						}
					}
				}
				else if (r0) {
					if (l1) {
						if (l[i][1] < r[i][1]) {
							add[l[i][1]].push_back({r[i][0], -1});
							if (r1)
								add[r[i][1]].push_back({i, r[i][0]});
						}
						else {
							add[l[i][1]].push_back({i, -1});
						}
					}
				}
				else {
					if (l1 && r1)
						add[max(l[i][1], r[i][1])].push_back({i, -1});
				}
			}
		}

		for (auto j : add[i]) {
			tree.upd(j.pos_add, -1);
			if (j.pos_del != -1)
				tree.upd(j.pos_del, 1);
		}

		cout << "tree = " << endl;
		for (auto j : tree.tree)
			cout << j << " ";
		cout << endl;

		for (auto j : rq[i])
			ans[j.ind] += tree.get(j.pos, i);
	}
}

void wr_ans() {
	cout << "ans = ";
	for (int i = 0; i < q; i++)
		cout << ans[i] << " ";
	cout << endl;
}

void run() {
	build();
	solve_L();
	for (int i = 0; i < n; i++) {
		for (auto j : rq[i]) {
			ans[j.ind] = i - j.pos + 1 - ans[j.ind];
		}
	}
}

void write() {
	for (int i = 0; i < q; i++)
		cout << ans[i] << " ";
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