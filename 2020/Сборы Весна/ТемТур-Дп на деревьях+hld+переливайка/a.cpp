#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10, MAXLOG = 19;

vector<int> g[MAXN];
int k;
int tin[MAXN], tout[MAXN], timer = 0;
int dp[MAXN][MAXLOG];

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v);
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

vector<pair<int, int>> q;

void read() {
	cin >> k;
	while (k--) {
		string s;
		cin >> s;
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (s == "ADD") {
			g[u].push_back(v);
			g[v].push_back(u);
		} else {
			q.push_back({u, v});
		}
	}
}

vector<int> ans;

void run() {
	dfs(0, 0);
	for (auto [u, v] : q) {
		ans.push_back(lca(u, v));
	}
}

void write() {
	for (auto i : ans)
		cout << i + 1 << "\n";
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