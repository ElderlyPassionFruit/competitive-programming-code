#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;

struct segment_tree{
	vector<pair<int, int> > tree;
	vector<int> pred;
	int n;

	segment_tree() {
		n = 0;
		pred = {};
		tree = {};
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = {a[tl], tl};
			pred[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(n * 4, {INF, 0});
		pred.assign(n, 0);
		build(1, 0, n, a);
	}

	void upd(int p, int val) {
		int v = pred[p];
		tree[v] = {val, p};
		v /= 2;
		while (v) {
			tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	pair <int, int> get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return {INF, INF};
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	pair <int, int> get(int l, int r) {
		auto fans = get(1, 0, n, l, r + 1);
		if (fans.first == INF)
			return {INF, INF};
		auto fans1 = get(1, 0, n, l, fans.second);
		auto fans2 = get(1, 0, n, fans.second + 1, r + 1);
		return {fans.first, min(fans1.first, fans2.first)};
	}	
};

int n, m;
vector<int> a;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

segment_tree tree[10];
int pows[10];

void build() {
	pows[0] = 1;
	for (int i = 1; i <= 9; i++) {
		pows[i] = pows[i - 1] * 10;
		vector<int> b;
		for (auto j : a) {
			if (j >= pows[i - 1] && j < pows[i]) {
				b.push_back(j);
			}
			else {
				b.push_back(INF);
			}
		}
		tree[i] = segment_tree(b);
	}
}

void upd(int pos, int val) {
	for (int i = 1; i <= 9; i++) {
		if (pows[i - 1] <= a[pos] && pows[i] > a[pos]) {
			tree[i].upd(pos, INF);
		}
	}
	a[pos] = val;
	for (int i = 1; i <= 9; i++) {
		if (pows[i - 1] <= a[pos] && pows[i] > a[pos]) {
			tree[i].upd(pos, a[pos]);
		}
	}
}

bool check(int a, int b) {
	int x = a + b;
	while (x) {
		if (!(x % 10 == a % 10 && a > 0) && !(x % 10 == b % 10 && b > 0))
			return false;
		x /= 10;
		a /= 10;
		b /= 10;
	}
	return true;
}

int get(int l, int r) {
	vector<int> help;
	for (int i = 1; i <= 9; i++) {
		pair <int, int> fans = tree[i].get(l, r);
		if (fans.first != INF)
			help.push_back(fans.first);
		if (fans.second != INF)
			help.push_back(fans.second);
	}
	vector<int> help2;
	for (auto i : help) {
		int x = 0;
		for (int j = 0; j < 9; j++) {
			x *= 2;
			x ^= (i > 0);
			i /= 10;
		}
		help2.push_back(x);
	}
	//sort(help.begin(), help.end());
	int ans = 2 * INF;
	for (int i = 0; i < help.size(); i++) {
		for (int j = i + 1; j < help.size(); j++) {
			//if (help[i] + help[j] >= ans) break;
			if (help2[i] & help2[j])
				chkmin(ans, help[i] + help[j]);
		}
	}
	if (ans == 2 * INF)
		ans = -1;
	return ans;
}

void run() {
	build();
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			int pos, val;
			cin >> pos >> val;
			pos--;
			upd(pos, val);
		}
		else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cout << get(l, r) << "\n";
		}
	}
}

void write() {

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