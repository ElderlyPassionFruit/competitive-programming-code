#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0) return 1;
	if (n & 1) {
		return mul(a, binpow(a, n - 1));
	} else {
		return binpow(mul(a, a), n / 2);
	}
}

int inv(int a) {
	return binpow(a, MOD - 2);
}

const int MAXN = 2e5 + 10;
int fact[MAXN], rfact[MAXN];

void build() {
	fact[0] = rfact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = mul(fact[i - 1], i);
		rfact[i] = inv(fact[i]);
	}
}

int c_n_k(int n, int k) {
	return mul(fact[n], mul(rfact[n - k], rfact[k]));
}

int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}	
}

int merge(int a, int sz_a, int b, int sz_b) {
	int ans = mul(a, b);
	ans = mul(ans, c_n_k(sz_a + sz_b, sz_a));
	return ans;
}

int dp[MAXN];
int sz[MAXN];
void dfs_down(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_down(i, v);
		sz[v] += sz[i];
	}

	int sz_now = 0;
	dp[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		dp[v] = merge(dp[v], sz_now, dp[i], sz[i]);
		sz_now += sz[i];
	}
}

int ans[MAXN];

void dfs_up(int v, int p) {
	if (p != -1) {
		int val_p = dp[p];
		int sz_p = n - sz[v] - 1;
		val_p = mul(val_p, inv(dp[v]));
		val_p = mul(val_p, inv(c_n_k(n - 1, sz[v])));
		dp[v] = merge(dp[v], sz_p + 1, val_p, sz[v] - 1);
	}

	for (auto i : g[v]) {
		if (i != p) {
			dfs_up(i, v);
		}
	}
}

void run() {
	build();
	dfs_down(0, 0);
	dfs_up(0, -1);
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << dp[i] << "\n";
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