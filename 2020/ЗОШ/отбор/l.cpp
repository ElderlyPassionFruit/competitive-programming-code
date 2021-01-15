#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

const int MAXN = 1e6 + 10;
int n;
int color[MAXN];
int root;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p >> color[i];
		if (p == 0) {
			root = i;
			continue;
		}
		p--;
		g[p].push_back(i);
	}		
}

const int MAXLOG = 21;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;

void dfs_lca(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		dfs_lca(i, v);
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

int ans[MAXN];
int last[MAXN];

void build() {
	dfs_lca(root, root);
	for (int i = 0; i <= n; i++)
		ans[i] = 1, last[i] = -1;
}

void dfs_calc(int v) {
	if (last[color[v]] != -1) {
		ans[lca(v, last[color[v]])]--;
	}
	last[color[v]] = v;
	for (auto i : g[v])
		dfs_calc(i);
}

void dfs_ans(int v) {
	for (auto i : g[v]) {
		dfs_ans(i);
		ans[v] += ans[i];
	}
}

void run() {
	build();
	dfs_calc(root);
	dfs_ans(root);
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}