#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;
#define int ll
ll tree[MAXN];
int n, m;
int a[MAXN];

int get(int r) {
	int ans = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		ans += tree[r];
	return ans;
}
int get(int l, int r) {
	return get(r) - get(l - 1);
}
void upd(int pos, int val) {
	for (; pos < n; pos |= pos + 1)
		tree[pos] += val;
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

const int MAXC = 1e6 + 10;
int val[MAXC];
int par[MAXN], mx[MAXN];

void precalc() {
	for (int i = 0; i < MAXN; i++)
		par[i] = i, mx[i] = i;
	for (int i = 1; i < MAXC; i++) {
		for (int j = i; j < MAXC; j += i) {
			val[j]++;
		}
	}
}

int get_par(int v) {
	if (v == par[v]) return v;
	return par[v] = get_par(par[v]);
}

void uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	par[a] = b;
	chkmax(mx[b], mx[a]);
}

void Upd(int pos, int val1) {
	upd(pos, -a[pos]);
	a[pos] = val1;
	upd(pos, a[pos]);
	if (val[a[pos]] == a[pos]) {
		uni(pos, pos + 1);
	}
}

int get_nxt(int pos) {
	return mx[get_par(pos)];
}

vector<int> ans;

void run() {
	precalc();
	for (int i = 0; i < n; i++) {
		upd(i, a[i]);
		if (val[a[i]] == a[i]) {
			uni(i, i + 1);
		}
	}
	for (int i = 0; i < m; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		l--;
		r--;
		if (t == 1) {
			int pos = get_nxt(l);
			while (pos <= r) {
				Upd(pos, val[a[pos]]);
				pos++;
				pos = get_nxt(pos);
			}
		} else {
			ans.push_back(get(l, r));
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