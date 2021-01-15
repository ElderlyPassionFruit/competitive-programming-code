#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const long long INF = 1e18 + 10;

struct line{
	long long k, b;
	line() {
		k = 0, b = -INF;
	}
	line(long long x, long long y) {
		k = x, b = y;
	}
};

long long eval(line l, long long x) {
	return l.k * x + l.b;
}

struct node {
	line x;
	node *l, *r;
	node() {
		x = {};
		l = nullptr;
		r = nullptr;
	}
	node(line new_line) {
		x = new_line;
		l = nullptr;
		r = nullptr;
	}
};

node * add(line x, node * tree, long long tl, long long tr) {
	long long tm = (tl + tr) / 2;
	bool mid = eval(tree->x, tm) < eval(x, tm);
	bool left = eval(tree->x, tl) < eval(x, tl);
	if (mid) {
		swap(tree->x, x);
	}
	if (tl == tr - 1) 
		return tree;
	if (left != mid) {
		if (tree->l == nullptr)
			tree->l = new node();
		add(x, tree->l, tl, tm);
	} 
	else {
		if (tree->r == nullptr) 
			tree->r = new node();
		add(x, tree->r, tm, tr);
	}
	return tree;
}

long long get(long long x, node * tree, long long tl, long long tr) {
	if (tree == nullptr) return -INF;
	if (tl >= x + 1 || tr <= x) return -INF;
	if (tl == tr - 1) return eval(tree->x, x);
	long long ans = eval(tree->x, x);
	long long tm = (tl + tr) / 2;
	chkmax(ans, get(x, tree->l, tl, tm));
	chkmax(ans, get(x, tree->r, tm, tr));
	return ans;
}

const long long MAXN = 1e5 + 10;
long long x[MAXN], c[MAXN], t[MAXN];
long long n;
long long dp[MAXN];

void read() {
	cin >> n;
	for (long long i = 1; i <= n; i++) {
		cin >> x[i] >> c[i] >> t[i];
	}
}

long long MAXC = 1e6 + 10;

long long ans;

void run() {
	dp[1] = 0;
	node * tree1 = new node(line(c[1], dp[1] - c[1] * x[1]));
	node * tree2 = new node(line(-c[1], dp[1] + c[1] * x[1]));
	for (long long i = 2; i <= n; i++) {
		long long ans1 = get(x[i], tree1, -MAXC, MAXC);
		long long ans2 = get(x[i], tree2, -MAXC, MAXC);
		dp[i] = max(ans1, ans2) + t[i];
		tree1 = add(line(c[i], dp[i] - c[i] * x[i]), tree1, -MAXC, MAXC);
		tree2 = add(line(-c[i], dp[i] + c[i] * x[i]), tree2, -MAXC, MAXC);
	}
	ans = dp[n];
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