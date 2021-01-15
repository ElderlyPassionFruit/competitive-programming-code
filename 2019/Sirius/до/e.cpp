#pragma GCC optimize("Ofast,unroll-loops,fast-math,no-stack-protector")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,mmx,popcnt,tune=native,avx,avx2")

#include <bits/stdc++.h>

using namespace std;
//#define int long long
const long long INF = -1e11;

struct node{
	double left_num, left_num2, right_num, right_num2;
	double ans;
	node() {
		left_num = INF;
		left_num2 = INF;
		right_num = INF;
		right_num2 = INF;
		ans = INF;
	}
};

const int MAXN = 5 * 1e5 + 10;
node tree[MAXN * 4];
long long mod[MAXN * 4];
double arr[MAXN];
int pos[MAXN * 4];

node merge(node a, node b) {	
	node ans;
	ans.ans = max(a.ans, b.ans);
	ans.ans = max(ans.ans, (a.right_num + b.left_num) / 2);
	ans.ans = max(ans.ans, (a.right_num2 + a.right_num + b.left_num) / 3);
	ans.ans = max(ans.ans, (a.right_num + b.left_num + b.left_num2) / 3);
	ans.left_num = a.left_num;
	ans.right_num = b.right_num;

	if (a.left_num2 != INF) {
		ans.left_num2 = a.left_num2;
	}
	else {
		ans.left_num2 = b.left_num;
	}
	if (b.right_num2 != INF) {
		ans.right_num2 = b.right_num2;
	}
	else {
		ans.right_num2 = a.right_num;
	}
	return ans;
}

void build(int v, int l, int r) {
	mod[v] = 0;
	if (l == r - 1) {
		node help;
		help.left_num = arr[l];
		help.right_num = arr[l];
		tree[v] = help;
		pos[l] = v;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

inline void push(int v) {
	mod[v * 2] += mod[v];
	mod[v * 2 + 1] += mod[v];
	mod[v] = 0;
}

inline node get_val(int v) {
	node ans = tree[v];
	ans.ans += mod[v];
	ans.left_num += mod[v];
	ans.right_num += mod[v];
	if (ans.left_num2 != INF)
		ans.left_num2 += mod[v];
	if (ans.right_num2 != INF)
		ans.right_num2 += mod[v];
	return ans;
}

void upd(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) {
		return;
	}
	if (tl >= l && tr <= r) {
		mod[v] += val;
		return;
	}
	push(v);
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
}

void upd(int v, int tl, int tr, int pos, int val) {
	if (tl >= pos + 1 || tr <= pos)
		return;
	if (tl == pos && tr == pos + 1) {
		mod[v] += val;
		tree[v] = get_val(v);
		mod[v] = 0;
		return;
	}
	push(v);
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, pos, val);
	upd(v * 2 + 1, tm, tr, pos, val);
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
}

void set_val(int ind, int val) {
	int v = pos[ind];
	mod[v] += val;
	tree[v] = get_val(v);
	mod[v] = 0;
	v /= 2;
	while (v) {
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		v /= 2;
	}
}

node get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l){
		return node();
	}
	if (tl >= l && tr <= r) {
		return get_val(v);
	}
	push(v);
	int tm = (tl + tr) / 2;
	node ans = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	return ans;
}

int n, q;
void upd(int l, int r, int val) {
	l--;
	r--;
	if ((r - l + 1) > 4) {
		upd(1, 0, n, l + 2, r - 1, val);

		set_val(l, val);
		set_val(l + 1, val);
		set_val(r - 1, val);
		set_val(r, val);

		/*upd(1, 0, n, l, val);
		upd(1, 0, n, l + 1, val);
		upd(1, 0, n, r - 1, val);
		upd(1, 0, n, r, val);*/
	}
	else {
		for (int i = l; i <= r; i++){
			set_val(i, val);
			//upd(1, 0, n, i, val);
		}
	}
}

double get(int l, int r) {
	l--;
	r--;
	node ans = get(1, 0, n, l, r + 1);
	return ans.ans;
}

void build() {
	build(1, 0, n);
}

void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	build();
}

int l, r, x;

void run() {
	for (int test = 0; test < q; test++) {
		int type;
		cin >> type;
		if (type == 1) {		
			cin >> l >> r >> x;
			upd(l, r, x);
		}
		else if (type == 2) {
			cin >> l >> r;
			cout << get(l, r) << '\n';
		}
	}	
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(6);
	read();
	run();
	return 0;
}