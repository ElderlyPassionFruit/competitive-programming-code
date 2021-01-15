#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const short int MAXN = 310;
vector<short int> g[MAXN];
short int n;

void read() {
	cin >> n;
	for (short int i = 0; i < n - 1; i++) {
		short int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

short int dp[MAXN][MAXN * 2];
bool flag[MAXN][MAXN * 2];
vector<short int> par[MAXN][MAXN * 2];

void dfs(short int v) {
	for (auto to : g[v]) {
		dfs(to);
	}

	for (short int i = 1; i <= n; i++) {
		int fans = i;
		vector<short int> have;
		for (auto to : g[v]) {
			fans += dp[to][-i + n];			
			have.push_back(-i);
		}
		if (fans >= dp[v][i + n]) continue;
		dp[v][i + n] = fans;
		flag[v][i + n] = true;
		par[v][i + n] = have;
	}

	for (short int i = 0; i >= -n; i--) {
		if (g[v].empty() && i == 0) continue;
		int fans = 0;
		vector<short int> have;
		for (auto to : g[v]) {
			fans += dp[to][i + 1 + n];
			have.push_back(i + 1);
		}
		if (fans >= dp[v][i + n]) continue;
		dp[v][i + n] = fans;
		flag[v][i + n] = false;
		par[v][i + n] = have;
	}

	for (short int len = 1; len <= n; len++) {
		int fans = 0;
		vector<short int> have;
		for (short int j = 0; j < (short int) g[v].size(); j++) {
			fans += dp[g[v][j]][-len + 1 + n];
			have.push_back(-len + 1);
		}

		for (short int i = 0; i < (short int) g[v].size(); i++) {
			short int to = g[v][i];
			fans += dp[to][len + n] - dp[g[v][i]][-len + 1 + n];
			have[i] = len;
			if (fans < dp[v][len - 1 + n]) {
				dp[v][len - 1 + n] = fans;
				flag[v][len - 1 + n] = false;
				par[v][len - 1 + n] = have;
			}
			fans -= dp[to][len + n] - dp[g[v][i]][-len + 1 + n];
			have[i] = -len + 1;
		}
	}
}

short int sz[MAXN];

void dfs_sz(short int v, short int p) {
	sz[v] = 1;
	for (auto to : g[v]) {
		if (to == p) continue;
		dfs_sz(to, v);
		sz[v] += sz[to];
	}
}

void del_par() {
	dfs_sz(0, 0);
	for (short int i = 1; i < n; i++) {
		sort(all(g[i]), [&] (short int a, short int b) {return sz[a] < sz[b];});
		g[i].pop_back();
	}
}

void solve() {
	del_par();
	for (short int i = 0; i < n; i++) {
		for (short int len = -n; len <= n; len++) {
			dp[i][len + n] = n + 1;
		}
	}
	dfs(0);
}

short int ans;
short int cost[MAXN];

void dfs_make(short int v, short int len) {
	if (flag[v][len + n]) {
		cost[v] = len;
	} else {
		cost[v] = 0;
	}
	for (short int i = 0; i < (short int) g[v].size(); i++) {
		short int to = g[v][i];
		short int nxt = par[v][len + n][i];
		dfs_make(to, nxt);
	}
}

void make_ans() {
	short int pow = 0;
	for (short int i = 1; i <= n; i++) {
		if (dp[0][i + n] < dp[0][pow + n]) {
			pow = i;
		}
	}
	ans = dp[0][pow + n];
	dfs_make(0, pow);
}

void run() {
	solve();
	make_ans();
}

void write() {
	cout << ans << "\n";
	for (short int i = 0; i < n; i++) {
		cout << cost[i] << " ";
	}
	cout << "\n";
}

signed main() {
	freopen("bus.in", "r", stdin);
	freopen("bus.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
WA 57
input = 
6
1 2
1 3
3 4
3 5
5 6

ans = 
2

out = 
3


*/