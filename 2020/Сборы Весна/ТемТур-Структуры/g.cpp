#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const ll INF = 1e18 + 10;

struct line{
	ll k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll _k, ll _b) {
		k = _k, b = _b;
	} 
};

ll eval(line l, ll x) {
	return l.k * x + l.b;
}

struct node{
	int l, r;
	line x;
	node() {
		l = -1, r = -1, x = {};
	}
	node(line _x, int _l, int _r) {
		x = _x, l = _l, r = _r;
	}
};

const int MAXMEM = 1e6 + 10;
const ll L = 0, R = 1e6 + 228;
node tree[MAXMEM];
int topQ = 0;

struct cht{
	int root;
	cht() {
		root = -1;
	}

	int add(line x, int root, ll tl = L, ll tr = R) {
		if (root == -1) {
			root = topQ++;
			tree[root].x = x;
			return root;
		}
		ll tm = (tl + tr) / 2;
		bool left = eval(x, tl) < eval(tree[root].x, tl);
		bool mid = eval(x, tm) < eval(tree[root].x, tm);
		if (mid) {
			swap(x, tree[root].x);
		}
		if (tl == tr - 1) {
			return root;
		}
		if (left != mid) {
			tree[root].l = add(x, tree[root].l, tl, tm);
		} else {
			tree[root].r = add(x, tree[root].r, tm, tr);
		}
		return root;
	}

	void add(line l) {
		root = add(l, root);
	}

	ll get(ll x, int root, ll tl = L, ll tr = R) {
		if (tl >= x + 1 || tr <= x) return INF;
		if (root == -1) return INF;
		if (tl == tr - 1) return eval(tree[root].x, x);
		int tm = (tl + tr) / 2;
		ll ans = eval(tree[root].x, x);
		chkmin(ans, get(x, tree[root].l, tl, tm));
		chkmin(ans, get(x, tree[root].r, tm, tr));
		return ans;
	}

	ll get(ll x) {
		return get(x, root);
	}
};

const int MAXN = 1e5 + 10;
int n;
int h[MAXN];
int w[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
}

cht fdp;
ll dp[MAXN];
ll pref[MAXN];

void run() {
	pref[0] = w[0];
	for (int i = 1; i < n; i++) {
		pref[i] = pref[i - 1] + w[i];
	}
	fdp = {};
	dp[0] = 0;
	fdp.add(line(-2LL * h[0], (ll)h[0] * h[0] + dp[0] - pref[0]));
	for (int i = 1; i < n; i++) {
		dp[i] = INF;
		chkmin(dp[i], fdp.get(h[i]) + (ll)h[i] * h[i] + pref[i - 1]);
		fdp.add(line(-2 * h[i], (ll)h[i] * h[i] + dp[i] - pref[i]));
	}
}

void write() {
	cout << dp[n - 1] << "\n";
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