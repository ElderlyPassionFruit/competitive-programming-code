#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e5 + 10;
vector<int> g[MAXN];
int n;
string s;

void read() {
	cin >> n;
	cin >> s;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
}

struct segment_tree{
	vector<int> tree;
	vector<int> pos;
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
		tree.assign(4 * n, 1e9);
		pos.assign(n, -1);
		build(1, 0, n);
	}
	void upd(int p, int val) {
		//tree[pos] = val;
		int v = pos[p];
		tree[v] = val;
		v /= 2;
		while (v) {
			tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	int get(int v, int tl, int tr, int l, int r, int k) {
		if (tl >= r || tr <= l) return -1;
		if (tree[v] >= k) return -1;
		if (tl == tr - 1) {
			return tl;
		}
		int tm = (tl + tr) / 2;
		int ans = get(v * 2 + 1, tm, tr, l, r, k);
		if (ans == -1)
			ans = get(v * 2, tl, tm, l, r, k);
		return ans;
	}

	int get(int r, int val) {
		return get(1, 0, n, 0, r + 1, val);
	}
};

map<int, int> have;
segment_tree tree;
ll ans[MAXN];
vector<char> st;
vector<int> st_bal;
vector<int> cnt;

void dfs(int v, int h, int bal) {
	if (s[v] == '(') bal++; else bal--;
	if (s[v] == '(') have[bal]++;
	st.push_back(s[v]);
	st_bal.push_back(bal);
	cnt.push_back(have[bal + 1]);

	tree.upd(h, bal);
	if (s[v] == ')') {
		int pos = tree.get(h, bal);
		if (pos == -1) ans[v] += have[bal + 1];
		else ans[v] += have[bal + 1] - cnt[pos + 1] + (st[pos + 1] == '(' && st_bal[pos + 1] == bal + 1);
	}

	for (auto i : g[v]) {
		ans[i] += ans[v];
		dfs(i, h + 1, bal);
	}

	if (s[v] == '(') have[bal]--;	
	st.pop_back();
	st_bal.pop_back();
	cnt.pop_back();
}

ll out;

void run() {
	tree = segment_tree(n);
	dfs(0, 0, 0);
	out = 0;
	for (int i = 0; i < n; i++) {
		out = out ^ (ans[i] * (i + 1));
	}
}

void write() {
	cout << out << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cerr.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
7
()()()(
1 2 2 3 5 3 


8
()()(()(
1 2 2 4 5 6 3 

*/