//#pragma GCC optimize("SEX_ON_THE_BEACH")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,popcnt,tune=native")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rev(x) reverse(all(x))
#define pbc push_back
#define pob pop_back()
#define mx(x) *max_element(all(x))
#define mn(x) *min_element(all(x))
#define rall(x) x.rbegin(), x.rend()
#define vin(v) for(auto &i : v) cin >> i;
#define vout(v, c) for (auto &i : v) cout << i << c;
#define endl '\n'
#define gcd(a, b) __gcd(a, b)
#define pop_cnt(a) __builtin_popcount(a)

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template<typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(NULL));

const int inf = 1e9 + 10;
const ll INF = 1e18 + 10;
const int MAXN = 1e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

struct segment_tree{
	vector<int> mod, tree;
	int n;

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
	}

	segment_tree() {
		n = 0;
		tree = {};
		mod = {};
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(n * 4, 0);
		mod.assign(n * 4, -1);
		build(1, 0, n, a);
	}

	void push(int v) {
		if (mod[v] == -1)
			return;
		if (v * 2 < n * 4)
			chkmax(mod[v * 2], mod[v]);
		if (v * 2 + 1 < n * 4)
			chkmax(mod[v * 2 + 1], mod[v]);
		chkmax(tree[v], mod[v]);
		mod[v] = -1;
	}

	void upd(int x) {
		chkmax(mod[1], x);
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return;
		push(v);
		if (tl == l && tr == r) {
			tree[v] = val;
			return;
		}
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
	}

	void upd(int pos, int val) {
		upd(1, 0, n, pos, pos + 1, val);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return -1e9;
		push(v);
		if (tl == l && tr == r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int pos) {
		return get(1, 0, n, pos, pos + 1);
	}
};

int n;
vector<int> a;
segment_tree tree;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	tree = segment_tree(a);
}

vector<int> ans;

void run() {
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int pos, val;
			cin >> pos >> val;
			pos--;
			tree.upd(pos, val);
		}
		if (type == 2) {
			int x;
			cin >> x;
			tree.upd(x);
		}
	}
	ans.assign(n, 0);
	for (int i = 0; i < n; i++)
		ans[i] = tree.get(i);
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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