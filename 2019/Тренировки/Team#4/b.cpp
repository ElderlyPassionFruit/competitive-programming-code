#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment_tree{
	vector<int> tree;
	vector<int> mod;
	vector<int> pos;

	int n;
	segment_tree() {
		n = 0;
		tree = {};
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(n * 4, 0);
		mod.assign(n * 4, 0);
		pos.resize(n);
		build(1, 0, n, a);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
	}

	int get_ans(int v) {
		return max(tree[v] - mod[v], 1LL); 
	}

	void upd(int v, int tl, int tr, int l, int r) {
		//cout << "v1 = " << v << endl; 
		if (tl >= r || tr <= l)
			return;
		if (tl >= l && tr <= r) {
			mod[v]++;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r);
		upd(v * 2 + 1, tm, tr, l, r);
	}

	void del(int l, int r) {
		upd(1, 0, n, l, r + 1);
	}

	int get(int p) {
		int v = pos[p];
		int x = tree[v];
		while (v) {
			x -= mod[v];
			v /= 2;
		}
		return max(x, 1LL);
	}
};

int n, q;
vector<int> a;
segment_tree tree;
void read() {
	cin >> n >> q;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	tree = segment_tree(a);
}

set <int> pos;

void del(int l, int r) {
	tree.del(l, r);
}

int get(int l, int r, int x) {
	auto it = pos.lower_bound(l);
	while (true) {
		if (*it > r) break;
		int have = tree.get(*it);
		auto it2 = next(it);
		x /= have;
		if (x == 0)
			return (*it) + 1; 
		if (have == 1)
			pos.erase(it);
		it = it2;
	}
	return -1;
}

vector<int> ans;
void run() {
	pos.insert(n);
	for (int i = 0; i < n; i++)
		pos.insert(i);
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			del(l, r);
		}
		else {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			r--;
			ans.push_back(get(l, r, x));
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