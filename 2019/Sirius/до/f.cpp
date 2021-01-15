#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;

const int B = 43;
const int MOD = 1e9 + 7;
const int INF = 1e18 + 2281337;
const int MAXN = 1e5 + 10;

int pows[MAXN], pref[MAXN];
int tree[MAXN * 4];
int mod[MAXN * 4];
int sz[MAXN * 4];
int arr[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

void build(int v, int l, int r) {
	mod[v] = INF;
	if (l == r - 1) {
		tree[v] = (pows[1] * arr[l]) % MOD;
		sz[v] = 1;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	sz[v] = sz[v * 2] + sz[v * 2 + 1];
	tree[v] = (tree[v * 2] + (tree[v * 2 + 1] * pows[sz[v * 2]]) % MOD) % MOD;
}

inline void push(int v) {
	if (mod[v] == INF)
		return;
	mod[v * 2] = mod[v];
	mod[v * 2 + 1] = mod[v];
	mod[v] = INF;
}

inline int get_val(int v) {
	if (mod[v] == INF)
		return tree[v];
	return (mod[v] * pref[sz[v]]) % MOD;
}

void upd(int v, int tl, int tr, int l, int r, int color) {
	if (tl >= r || tr <= l)
		return;
	if (tl >= l && tr <= r) {
		mod[v] = color;
		return;
	}
	push(v);
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, color);
	upd(v * 2 + 1, tm, tr,l, r, color);
	tree[v] = (get_val(v * 2) + (get_val(v * 2 + 1) * pows[sz[v * 2]]) % MOD) % MOD;
}

pair <int, int> get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l)
		return {0, 0};
	if (tl >= l && tr <= r)
		return {get_val(v), sz[v]};
	push(v);
	int tm = (tl + tr) / 2;
	auto x1 = get(v * 2, tl, tm, l, r);
	auto x2 = get(v * 2 + 1, tm, tr, l, r);
	int ans = (x1.first + (x2.first * pows[x1.second]) % MOD) % MOD;
	tree[v] = (get_val(v * 2) + (get_val(v * 2 + 1) * pows[sz[v * 2]]) % MOD) % MOD;
	return {ans, x1.second + x2.second};
}

void build() {
	build(1, 0, n);
	//for (int i = 0; i < n; i++)
	//	tree[i] = (arr[i] * pows[1]) % MOD;
}

void upd(int l, int r, int color){
	upd(1, 0, n, l, r + 1, color);
	//for (int i = l; i <= r; i++) {
	//	tree[i] = (color * pows[1]) % MOD;
	//}
}

int get(int l, int r) {
	return get(1, 0, n, l, r + 1).first; 
	//int ans = 0;
	//for (int i = l; i <= r; i++) {
	//	ans += tree[i] * pows[i - l];
	//	ans %= MOD;
	//}
	//return ans;
}


string ans;

void run() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = (B * pows[i - 1]) % MOD;
		pref[i] = (pref[i - 1] + pows[i]) % MOD;
	}

	build();
	ans = "";
	/*cerr << endl;
	cerr << "pows = ";
	for (int i = 0; i < MAXN; i++)
		cerr << pows[i] << " ";
	cerr << endl;
	cerr << "pref = ";
	for (int i = 0; i < MAXN; i++)
		cerr << pref[i] << " ";
	cerr << endl;
	*/
	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		int type, l, r, k;
		cin >> type >> l >> r >> k;
		l--;
		r--;
		if (type == 0) {
			upd(l, r, k);
		}
		else if (type == 1) {
			int h1 = get(l, l + k - 1);
			int h2 = get(r, r + k - 1);
			//cout << "h1 = " << h1 << " h2 = " << h2 << endl;
			if (h1 == h2) {
				ans += "+";
			}
			else {
				ans += "-";
			}
		}
	/*	cout << "hash = ";
		for (int i = 0; i < n; i++) {
			cout << get(i, i) << " ";
		}
		cout << endl;

		cout << "tree = ";
		for (int i = 0; i < MAXN; i++)
			cout << tree[i] << " ";
		cout << endl;

		cout << "mod = ";
		for (int i = 0; i < MAXN; i++)
			cout << mod[i] << " ";
		cout << endl;
		cout << endl;*/
	}
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