#include <bits/stdc++.h>

using namespace std;
//#define int long long

const int MAXN = 5 * 1e5 + 10, MAXLOG = 23;
vector<int> g[MAXN];
int n, k;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

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
	return tout[v] >= tout[u] && tin[v] <= tin[u];
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
	cin >> n >> k;
	set<int> root;
	for (int i = 0; i < n; i++)
		root.insert(i);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		root.erase(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	assert(root.size() == 1);
	dfs(*root.begin(), *root.begin(), 0);
}

vector<vector<int>> ans;

void run() {
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		int fans = h[lca(a, b)];
		ans.push_back({a + 1, b + 1, fans}); 
	}
}

void write() {
	for (auto i : ans)
		cout << i[0] << " " << i[1] << " " << i[2] << "\n"; 
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