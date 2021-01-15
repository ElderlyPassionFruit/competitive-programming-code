#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e5 + 10, MAXLOG = 20;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;
vector <pair <int, int> > g[MAXN];
int min_zero[MAXN][MAXLOG];
int sum_one[MAXN];
int sum_all[MAXN];
int h[MAXN];
int cnt_zero[MAXN];

const int INF = 1e18 + 10;

void dfs(int v, int p, int len, int ed, int full, int one, int cnt) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	if (ed % 2 == 0)
		min_zero[v][0] = ed;
	for (int i = 1; i < MAXLOG; i++)
		min_zero[v][i] = min(min_zero[v][i - 1], min_zero[dp[v][i - 1]][i - 1]);

	cnt_zero[v] = cnt;
	sum_one[v] = one;
	sum_all[v] = full;
	h[v] = len;

	for (auto i : g[v]) {
		if (i.first != p) {
			dfs(i.first, v, len + 1, i.second, full + (i.second), one + i.second * (i.second % 2), cnt + 1 - i.second % 2);
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

int get_len(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

int get_sum(int v, int u) {
	return sum_all[v] + sum_all[u] - 2 * sum_all[(lca(v, u))];
}

int get_one(int v, int u) {
	return sum_one[v] + sum_one[u] - 2 * sum_one[(lca(v, u))];
}

int get_cnt(int v, int u) {
	return cnt_zero[v] + cnt_zero[u] - 2 * cnt_zero[lca(v, u)];
}

int get_min_on_path(int v, int u) {
	if (v == u) return INF;
	int ans = INF;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[u][i], v)) {
			ans = min(ans, min_zero[u][i]);
			u = dp[u][i];
		}
	ans = min(ans, min_zero[u][0]);
	return ans;
}

int get_min(int v, int u) {
	int l = lca(v, u);
	return min(get_min_on_path(l, v), get_min_on_path(l, u));
}

void make() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXLOG; j++)
			min_zero[i][j] = INF;
	dfs(0, 0, 0, INF, 0, 0, 0);
}

int full = 0;
int n, q;
void read() {
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		full += cost;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
	make();
}

vector <int> ans;
void run() {
	ans.resize(q);
	for (int test = 0; test < q; test++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		int len = get_len(a, b);
		int all = get_sum(a, b);
		int min_el = get_min(a, b);
		int one = get_one(a, b);
		int zero = all - one;

		if (min_el - 1 < len - 2) {
			ans[test] = 2;
			continue;
		}


		int cnt = get_cnt(a, b);
		if (cnt <= 1) {
			ans[test] = 1;
			continue;
		}
		if (cnt > 2) {
			ans[test] = 2;
			continue;
		}

		int have = full - zero;
		have %= 2;

		if (have == 1) {
			ans[test] = 1;
		}
		else {
			ans[test] = 2;
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}