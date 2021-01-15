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
const int MAXN = 2e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

const int MAXLOG = 20;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;
vector<int> g[MAXN];
int n;

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v);
		}
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

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

bool check(int u, int v, int x) {
	return is_upper(u, x) && is_upper(x, v);
}

vector<bool> ans;

void run() {
	dfs(0, 0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int r, b;
		cin >> r >> b;
		vector<int> vert_r;
		int v;
		cin >> v;
		v--;
		vert_r.push_back(v);
		for (int j = 0; j < r - 1; j++) {
			int x;
			cin >> x;
			x--;
			vert_r.push_back(x);
			v = lca(v, x);
		}

		vector<int> vert_b;
		int u;
		cin >> u;
		u--;
		vert_b.push_back(u);
		for (int j = 0; j < b - 1; j++) {
			int x;
			cin >> x;
			x--;
			vert_b.push_back(x);
			u = lca(u, x);
		}

		bool flag = false;
		for (auto i : vert_r) {
			flag |= check(v, i, u);
		}
		for (auto i : vert_b) {
			flag |= check(u, i, v);
		}
		ans.push_back(!flag);
	}
}

void write() {
	for (auto i : ans)
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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