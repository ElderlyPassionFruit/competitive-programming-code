#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;
vector<int> g[MAXN];

void dfs(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs(i, v, len);
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

int pre_lca(int v, int u) {
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return v;
}

int n, q;

void read() {
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int x;
		cin >> x;
		x--;
		g[i].push_back(x);
		g[x].push_back(i);
	}
}

int check(int s, int f, int t) {
	int lca_s_f = lca(s, f);
	int lca_s_t = lca(s, t);
	int lca_t_f = lca(t, f);
	bool flag1 = lca_s_f == f, flag2 = lca_t_f == f;
	if (flag1 != flag2) {
		return 1;
	}
	if (flag1) {
		return max(1LL, h[lca_s_t] - h[f] + 1);
	}
	if (lca_s_f == lca_t_f) {
		return max(1LL, h[lca_s_t] + h[f] - 2 * h[lca_t_f] + 1);
	}
	else {
		return max(1LL, h[f] - max(h[lca_s_f], h[lca_t_f]) + 1);
	}
}

int solve(int a, int b, int c) {
	int ans = 0;
	vector<int> x = {a, b, c};
	sort(x.begin(), x.end());
	do {
		chkmax(ans, check(x[0], x[1], x[2]));
	} while (next_permutation(x.begin(), x.end()));
	return ans;
}

vector<int> ans;

void run() {
	dfs(0, 0, 0);
	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		ans.push_back(solve(a, b, c));
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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