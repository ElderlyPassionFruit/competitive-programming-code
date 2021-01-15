#pragma GCC optimize("Ofast,unroll-loops,fast-math,no-stack-protector")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,mmx,tune=native,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()
#define ld double
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const double INF = -1e12;

struct node{
	ld l1, l2, r1, r2;
	ld ans;
	node() {
		ans = INF;
		l1 = INF;
		l2 = INF;
		r1 = INF;
		r2 = INF;
	}
	node(int x) {
		l1 = x;
		r1 = x;
		l2 = INF;
		r2 = INF;
		ans = INF;
	}
};

inline node merge(const node & a, const node & b) {
	node ans = node();
	chkmax(ans.ans, a.ans);
	chkmax(ans.ans, b.ans);
	chkmax(ans.ans, (a.r1 + b.l1) / 2);
	chkmax(ans.ans, (a.r1 + b.l1 + b.l2) / 3);
	chkmax(ans.ans, (a.r2 + a.r1 + b.l1) / 3);
	ans.l1 = a.l1;
	ans.r1 = b.r1;
	if (a.l2 != INF) {
		ans.l2 = a.l2;
	}
	else {
		ans.l2 = b.l1;
	}
	if (b.r2 != INF) {
		ans.r2 = b.r2;
	}
	else {
		ans.r2 = a.r1;
	}
	return ans;
}
	
const int MAXN = 5e5 + 10;
node tree[MAXN * 4];
long long mod[MAXN * 4];
int pos[MAXN];
int a[MAXN];
int n;

void build(int v, int tl, int tr) {
	mod[v] = 0;
	if (tl == tr - 1) {
		tree[v] = node(a[tl]);
		pos[tl] = v;
		return;
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm, tr);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void build() {
	build(1, 0, n);
}

inline void push(int v) {
	mod[v * 2] += mod[v];
	mod[v * 2 + 1] += mod[v];
	mod[v] = 0;
}

inline node get_val(int v) {
	node ans = tree[v];
	ans.ans += mod[v];
	ans.l1 += mod[v];
	ans.r1 += mod[v];
	if (ans.l2 != INF)
		ans.l2 += mod[v];
	if (ans.r2 != INF)
		ans.r2 += mod[v];
	return ans;
}

inline node get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return node();
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

inline ld get(int l, int r) {
	return get(1, 0, n, l, r + 1).ans;
}

inline void upd(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) return;
	if (tl >= l && tr <= r) {
		mod[v] += val;
		return;
	}
	int tm = (tl + tr) / 2;
	push(v);
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
}

inline void add_val(int p, int val) {
	int v = pos[p];
	mod[v] += val;
	tree[v] = get_val(v);
	mod[v] = 0;
	v /= 2;
	while (v) {
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		v /= 2;
	}
}

inline void upd(int l, int r, int val) {
	if ((r - l + 1) > 4) {
		add_val(l, val);
		add_val(l + 1, val);
		add_val(r, val);
		add_val(r - 1, val);
		upd(1, 0, n, l + 2, r - 1, val);
	}
	else {
		for (int i = l; i <= r; i++)
			add_val(i, val);
	}
}


int q;

void read() {
	scanf("%d%d",&n,&q);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);
}

void run() {
	build();
	for (int test = 0; test < q; test++) {
		int type;
		scanf("%d",&type);
		if (type == 1) {
			int l, r, x;
			scanf("%d%d%d",&l,&r,&x);
			l--;
			r--;
			upd(l, r, x);
		}
		else if (type == 2) {
			int l, r;
			scanf("%d%d",&l,&r);
			l--;
			r--;
			cout << fixed << setprecision(6) << get(l, r) << '\n';
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